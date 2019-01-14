#pragma once

#include "../../cipher/StockBlockCipher.h"
#include "A1Circular64BitShift.h"
#include "A1SubBytes.h"
#include "A1CombineKey.h"
#include "A1KeyCycle.h"

#include <memory>

#define A1_STATE_BITS 512
#define A1_STATE_BYTES (A1_STATE_BITS / 8)

#define A1_KEY_BITS A1_STATE_BITS
#define A1_KEY_BYTES (A1_KEY_BITS / 8)

namespace TroyCrypt {

class A1 : public StockBlockCipher<A1_KEY_BYTES>
{
public:
	void encryptBlock(BlockContext* context);
	void decryptBlock(BlockContext* context);

	static std::unique_ptr<BlockContext> newContext();
private:
	A1SubBytes subBytes;
	A1Circular64BitShift bitRotate;
	A1CombineKey combineKey;
	A1KeyCycle keyCycle;
};

}