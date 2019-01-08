#pragma once

#include "../../cipher/ConstantLengthBlockCipher.h"
#include "A1Circular32BitShift.h"
#include "A1SubBytes.h"
#include "A1CombineKey.h"

#define A1_STATE_BITS 512
#define A1_STATE_BYTES (A1_STATE_BITS / 8)

#define A1_KEY_BITS 512
#define A1_KEY_BYTES (A1_KEY_BITS / 8)

namespace TroyCrypt {

	class A1 : public ConstantLengthBlockCipher<A1_STATE_BYTES>
	{
	public:
		void encryptBlock(u8* plainText, u8* cipherText, u8* key);
		void decryptBlock(u8* plainText, u8* cipherText, u8* key);
	private:
		A1SubBytes subBytes;
		A1Circular32BitShift bitRotate;
		A1CombineKey combineKey;
	};

}