#pragma once

#include "../../stage/BlockCipherStage.h"

namespace TroyCrypt {

	class A1Circular32BitShift : BlockCipherStage
	{

	public:
		void operate(u8* state, u32 stateSize);
		void inverse(u8* state, u32 stateSize);
	};
}

