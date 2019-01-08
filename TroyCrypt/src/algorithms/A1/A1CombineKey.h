#pragma once

#include "../../stage/BlockCipherStage.h"

namespace TroyCrypt {

	class A1CombineKey : BlockCipherStage
	{

	public:
		void operate(u8* state, u32 stateSize, u8* key);
		void inverse(u8* state, u32 stateSize, u8* key);
	};
}

