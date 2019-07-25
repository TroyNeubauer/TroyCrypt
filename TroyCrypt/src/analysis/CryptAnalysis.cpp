
#include <random>
#include <math.h>

#include "CryptAnalysis.h"
#include "../util/HardwareRNG.h"
#include "../util/Utils.h"

namespace TroyCrypt {


	std::ostream & operator<<(std::ostream & os, const FrequencyResult& result) {
		os << "Frequency Analysis Results:" << std::endl;
		os << "General Score: " << result.overallRating << std::endl;
		os << "Sampled " << result.dataSize << " bytes. 0x" << std::hex << (int) result.mostFrequentValue << std::dec << " is the most common (" << result.frequency[result.mostFrequentValue];
		os << " times) and 0x" << std::hex << (int) result.leastFrequentValue << std::dec << " is the least common (" << result.frequency[result.leastFrequentValue] << " times)";
		return os;
	}

	std::ostream & operator<<(std::ostream & os, const DiffusionResult& result) {
		os << "Diffusion Analysis Results:" << std::endl;
		os << "General Score: " << result.overallRating << ", Key Bits: " << result.keyBits << std::endl;
		os << "Total Bits Flipped: " << result.totalFlip << std::endl;
		os << "Average Bits Flipped: " << result.averagePercentFlip << '%' << std::endl;
		os << "Min Bits Flipped: " << result.lowestFlip << '%' << std::endl;
		os << "Max Bits Flipped: " << result.highestFlip << '%' << std::endl;
		return os;
	}


	u64 getBitCount(u8* buffer, u64 length) {
		u64 result = 0;
		u64* buf64 = (u64*) buffer;
		while (length >= 8) {
			result += _mm_popcnt_u64(*buf64);
			length -= sizeof(u64);
			buf64++;
		}
		if (length > 0) {
			u64 last = 0;
			u64* lastAddr = &last;
			memcpy(lastAddr, buf64, length);
			result += _mm_popcnt_u64(last);
		}
		return result;
	}

	void massXOR(u8* a, u8* b, u8* result, u64 length) {
		u64* a64 = (u64*) a;
		u64* b64 = (u64*) b;
		u64* result64 = (u64*) result;
		while (length >= 8) {
			*result64 = *a64 ^ *b64;
			//Go to next word
			length -= sizeof(u64);
			a64++;
			b64++;
			result64++;
		}
		if (length > 0) {//Deal with last few bytes (<8)
			u64 aTemp = 0, bTemp = 0, resultTemp = 0;
			memcpy(&aTemp, a64, length);
			memcpy(&bTemp, b64, length);
			resultTemp = aTemp ^ bTemp;
			memcpy(result64, &resultTemp, length);
		}
	}

	void massXOR(u8* a, u8* b, u64 length) { 
		massXOR(a, b, a, length);
	}


	DiffusionResult doDiffusionAnalysis(u8* plainText, u8* cipherText, u64 length, TroyContext* context, TroyCipher* cipher) {
		DiffusionResult result = {};
		u64 minFlipped = -1, maxFlipped = -1;
		u64 totalFlipped = 0;
		u8* lastCipherText = new u8[length];
		//Get a baseline to compare with
		cipher->encrypt(plainText, lastCipherText, length, context);
		u64 keyBits = CHAR_BIT * context->m_KeyBytes;
		for (unsigned int i = 0; i < context->m_KeyBytes; i++) {
			for (int bit = 7; bit >= 0; bit--) {
				context->m_Key[i] ^= 1UL << bit;//Flip the bit
				cipher->encrypt(plainText, cipherText, length, context);
				massXOR(cipherText, lastCipherText, lastCipherText, length);

				u64 bitsFlipped = getBitCount(lastCipherText, length);
				totalFlipped += bitsFlipped;
				if (minFlipped == -1 || bitsFlipped < minFlipped)
					minFlipped = bitsFlipped;
				if (maxFlipped == -1 || bitsFlipped > maxFlipped)
					maxFlipped = bitsFlipped;

				context->m_Key[i] ^= 1UL << bit;//Flip the bit back
				memcpy(lastCipherText, cipherText, length);
			}
		}
		result.keyBits = CHAR_BIT * context->m_KeyBytes;
		result.lowestFlip = (double) minFlipped / result.keyBits * 100.0;
		result.highestFlip = (double) maxFlipped / result.keyBits * 100.0;
		result.totalFlip = totalFlipped;
		result.averagePercentFlip = (double) totalFlipped / ((double) result.keyBits * result.keyBits) * 100.0;
		delete[] lastCipherText;
		return result;
	}

	FrequencyResult doFrequencyAnalysis(u8* plainText, u8* cipherText, u64 length, TroyContext* context, TroyCipher* cipher, u32 iterations) {
		FrequencyResult result = {};
		HardwareRNG rng;
		for (unsigned int i = 0; i < iterations; i++) {
			rng.getBytes(context->m_Key, context->m_KeyBytes);//Generate a new key
			cipher->encrypt(plainText, cipherText, length, context);
			gatherFrequency(cipherText, length, result);
		}
		return result;
	}

	void gatherFrequency(u8* buffer, u64 length, FrequencyResult& result) {

		result.dataSize += length;
		for (int i = 0; i < length; i++) {
			u8 byte = buffer[i];
			result.frequency[byte]++;
		}
		u8 mostFrequentValue = 0, leastFrequentValue = 0;
		for (int i = 1; i < 256; i++) {
			u64 currentFrequency = result.frequency[i];
			if (currentFrequency > result.frequency[mostFrequentValue]) {
				mostFrequentValue = i;
			}
			if (currentFrequency < result.frequency[leastFrequentValue]) {
				leastFrequentValue = i;
			}
		}
		result.mostFrequentValue = mostFrequentValue;
		result.leastFrequentValue = leastFrequentValue;

		u64 idealFrequency = (result.dataSize - 1) / 256 + 1;
		u64 mostDelta = difference(result.frequency[mostFrequentValue], idealFrequency);
		u64 leastDelta = difference(idealFrequency, result.frequency[leastFrequentValue]);

		double mostScore = map((double) mostDelta, 0.0, (double) result.dataSize, 1.0, 0.0);
		double leastScore = map((double) leastDelta, 0.0, (double) result.dataSize, 1.0, 0.0);

		//Punish the bad algorithms by dropping their scores when far from 1.0
		mostScore = mostScore * mostScore * mostScore * mostScore * mostScore * mostScore;
		leastScore = leastScore * leastScore * leastScore * leastScore * leastScore * leastScore;

		result.overallRating = (mostScore + leastScore) * 50.0;//Map from [0, 2] to [0, 100]
	
	}


}