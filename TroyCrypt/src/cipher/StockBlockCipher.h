#pragma once

#include "BlockCipher.h"

#include <iostream>
#include "../util/Utils.h"

namespace TroyCrypt {
	
template<u32 SIZE> class StockBlockCipher : BlockCipher
{
public:
	void encrypt_BlockCipher(u8* plainText, u8* cipherText, u64 length, BlockContext* context)
	{
		context->m_BlockIteration = 0;
		context->m_Encrypting = true;
		context->m_TotalBlocks = length / context->m_BlockBytes;
		for (int i = 0; i < length; i += SIZE, plainText += SIZE, cipherText += SIZE, context->m_BlockIteration++) {
			std::memcpy((u8*) context->m_State, plainText, context->m_BlockBytes);
			encryptBlock(context);
			std::memcpy(cipherText, (u8*) context->m_State, context->m_BlockBytes);
		}
	}

	void decrypt_BlockCipher(u8* cipherText, u8* plainText, u64 length, BlockContext* context)
	{
		context->m_BlockIteration = 0;
		context->m_Encrypting = false;
		context->m_TotalBlocks = length / context->m_BlockBytes;
		for (int i = 0; i < length; i += SIZE, cipherText += SIZE, plainText += SIZE, context->m_BlockIteration++) {
			std::memcpy((u8*) context->m_State, cipherText, context->m_BlockBytes);
			decryptBlock(context);
			std::memcpy(plainText, (u8*) context->m_State, context->m_BlockBytes);
		}
	}
	virtual void encryptBlock(BlockContext* context) = 0;
	virtual void decryptBlock(BlockContext* context) = 0;
};
}
