#pragma once

#include "BlockCipherStage.h"
namespace TroyCrypt {

	class BlockCipherSubBytes : public BlockCipherStage
	{

	public:
		virtual void operate(u8* state, u32 stateSize) = 0;
		virtual void inverse(u8* state, u32 stateSize) = 0;
	};
}