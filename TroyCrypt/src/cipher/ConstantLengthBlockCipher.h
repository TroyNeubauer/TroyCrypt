#pragma once

#include "BlockCipher.h"

namespace TroyCrypt {
	
	template<u32 SIZE> class ConstantLengthBlockCipher : BlockCipher
	{
	public:
		void encrypt(u8* plainText, u8* cipherText, u64 length, u8* key)
		{
			for (int i = 0; i < length; i += SIZE)
				encryptBlock(plainText + i, cipherText + i, key);
		}
		void decrypt(u8* cipherText, u8* plainText, u64 length, u8* key)
		{
			for (int i = 0; i < length; i += SIZE)
				decryptBlock(cipherText + i, plainText + i, key);
		}
		virtual void encryptBlock(u8* plainText, u8* cipherText, u8* key) = 0;
		virtual void decryptBlock(u8* cipherText, u8* plainText, u8* key) = 0;

		u32 getStateSize()
		{
			return SIZE;
		}

		u8* getState()
		{
			return state;
		}

	private:
		u8 state[SIZE];
	};

}