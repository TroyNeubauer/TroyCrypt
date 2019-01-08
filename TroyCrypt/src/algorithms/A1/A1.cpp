#include "A1.h"

#define ROUND_COUNT 10

namespace TroyCrypt {
	void A1::encryptBlock(u8* plainText, u8* cipherText, u8* key)
	{
		std::memcpy(getState(), plainText, getStateSize());
		for (int i = 0; i < ROUND_COUNT; i++)
		{
			bitRotate.operate(getState(), getStateSize());
			subBytes.operate(getState(), getStateSize());
			combineKey.operate(getState(), getStateSize(), key);
		}
		std::memcpy(cipherText, getState(), getStateSize());
	}
	void A1::decryptBlock(u8* cipherText, u8* plainText, u8* key)
	{
		std::memcpy(getState(), cipherText, getStateSize());
		for (int i = 0; i < ROUND_COUNT; i++)
		{
			combineKey.inverse(getState(), getStateSize(), key);
			subBytes.inverse(getState(), getStateSize());
			bitRotate.inverse(getState(), getStateSize());
		}
		std::memcpy(plainText, getState(), getStateSize());
	}
}