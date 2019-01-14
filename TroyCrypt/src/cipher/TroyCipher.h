#pragma once

#include "../TroyCrypt.h"
#include "../TroyContext.h"

namespace TroyCrypt {

class TroyCipher
{

public:
	virtual void encrypt(u8* plainText, u8* cipherText, u64 length, TroyContext* context) = 0;
	virtual void decrypt(u8* cipherText, u8* plainText, u64 length, TroyContext* context) = 0;
};

}