#pragma once
#include "TroyCipher.h"

namespace TroyCrypt {

class BlockCipher : public TroyCipher
{
public:
	void encrypt(u8* plainText, u8* cipherText, u64 length, TroyContext* context);
	void decrypt(u8* cipherText, u8* plainText, u64 length, TroyContext* context);
	virtual void encrypt_BlockCipher(u8* plainText, u8* cipherText, u64 length, BlockContext* context) = 0;
	virtual void decrypt_BlockCipher(u8* cipherText, u8* plainText, u64 length, BlockContext* context) = 0;

};
}