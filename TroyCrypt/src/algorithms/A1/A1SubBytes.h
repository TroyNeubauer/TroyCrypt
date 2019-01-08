#pragma once


#include "../../stage/BlockCipherSubBytes.h"

namespace TroyCrypt {
	class A1SubBytes : public BlockCipherSubBytes {

	public:
		void operate(u8* state, u32 stateSize);
		void inverse(u8* state, u32 stateSize);
	};

}