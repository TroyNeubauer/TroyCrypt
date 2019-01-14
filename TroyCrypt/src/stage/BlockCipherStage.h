#pragma once

#include "CipherStage.h"

namespace TroyCrypt {

class BlockCipherStage : public CipherStage
{

public:
	void operate(TroyContext* context);
	void inverse(TroyContext* context);
	virtual void operate_BlockCipher(BlockContext* context) = 0;
	virtual void inverse_BlockCipher(BlockContext* context) = 0;
};
}