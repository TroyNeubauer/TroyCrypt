

#include <memory>
#include <iostream>
#include <nmmintrin.h>

#include "../TroyCrypt.h"
#include "../TroyContext.h"
#include "../cipher/TroyCipher.h"

namespace TroyCrypt {


template<typename T> 
T normalize(T min, T max, T value) {
	return (value - min) / (max - min);
}

template<typename T>
T lerp(T a, T b, T f) {
	return a + f * (b - a);
}

template<typename T>
T map(T value, T sourceMin, T sourceMax, T destMin, T destMax) {
	T n = normalize(sourceMin, sourceMax, value);
	return lerp(destMin, destMax, n);
}

template<typename T>
T difference(const T a, const T b) {
	return (a > b) ? (a - b) : (b - a);
}


struct FrequencyResult {
	//0-100 representing the over precentage of how good it is 100 means good a distribution
	float overallRating;
	u64 dataSize;

	u8 mostFrequentValue;
	u8 leastFrequentValue;
	
	//Each index contains the number of times that index appeared
	u64 frequency[256];

	friend std::ostream& operator<<(std::ostream & os, const FrequencyResult& result);
};

struct DiffusionResult {
	float averagePercentFlip;
	u64 totalSize, singleSize;
	u64 totalFlip;

	u32 lowestFlip, highestFlip;

	friend std::ostream& operator<<(std::ostream & os, const DiffusionResult& result);
};

u64 getBitCount(u8* buffer, u64 length);

//Computes XOR of a and b, storing the result in result
void massXOR(u8* a, u8* b, u8* result, u64 length);

//Computer XOR of a and b, storing the result back into a
void massXOR(u8* a, u8* b, u64 length);

DiffusionResult doDiffusionAnalysis(u8* plainText, u8* cipherText, u64 length, TroyContext* context, TroyCipher* cipher);

FrequencyResult doFrequencyAnalysis(u8* plainText, u8* cipherText, u64 length, TroyContext* context, TroyCipher* cipher, u32 iterations);

void gatherFrequency(u8* buffer, u64 length, FrequencyResult& result);


}
