#pragma once
#include "TroyCipher.h"

namespace TroyCrypt {

	class BlockCipher : public TroyCipher
	{
		virtual void encrypt(u8* plainText, u8* cipherText, u64 length, u8* key) = 0;
		virtual void decrypt(u8* cipherText, u8* plainText, u64 length, u8* key) = 0;

		virtual u32 getStateSize() = 0;
		virtual u8* getState() = 0;
	};
}