#include "A1Circular32BitShift.h"
#include <stdint.h>   // for uint32_t
#include <limits.h>   // for CHAR_BIT
#include <assert.h>
#include <intrin.h>


namespace TroyCrypt {

	void A1Circular32BitShift::operate(u8* state, u32 stateSize)
	{
		u16* state32 = (u16*) state;
		for (int i = 0; i < stateSize / sizeof(u16); i++)
		{
			state32[i] = _rotl16(state32[i], 11);
		}
	}

	void A1Circular32BitShift::inverse(u8* state, u32 stateSize)
	{
		u16* state32 = (u16*) state;
		for (int i = 0; i < stateSize / sizeof(u16); i++)
		{
			state32[i] = _rotr16(state32[i], 11);
		}
	}
}
