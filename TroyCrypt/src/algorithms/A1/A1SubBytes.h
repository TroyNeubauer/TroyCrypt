#pragma once


#include "../../stage/BlockCipherStage.h"

namespace TroyCrypt {
class A1SubBytes : public BlockCipherStage {

public:
	void operate_BlockCipher(BlockContext* context);
	void inverse_BlockCipher(BlockContext* context);
};

}