#pragma once

#include "BlockCipher.h"

namespace TroyCrypt {

	class DynamicBlockCipher : BlockCipher
	{
	public:
		DynamicBlockCipher(u32 stateSize);
		virtual void encrypt(u8* plainText, u8* cipherText, u64 length) = 0;
		virtual void decrypt(u8* cipherText, u8* plainText, u64 length) = 0;

		virtual u32 getStateSize() = 0;
		virtual u8* getState() = 0;

		~DynamicBlockCipher();
	private:
		u8 * m_State;
		u32 m_StateSize;
	};

}