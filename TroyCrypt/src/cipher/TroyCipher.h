#pragma once

#include "../TroyCrypt.h"

namespace TroyCrypt {

	class TroyCipher
	{

	public:
		virtual void encrypt(u8* plainText, u8* cipherText, u64 length, u8* key) = 0;
		virtual void decrypt(u8* cipherText, u8* plainText, u64 length, u8* key) = 0;
	};

}