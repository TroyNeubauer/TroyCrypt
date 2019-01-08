#include "A1CombineKey.h"

namespace TroyCrypt {

	void A1CombineKey::operate(u8* state, u32 stateSize, u8* key)
	{
		u32* state32 = (u32*) state;
		u32* key32 = (u32*) key;
		for (int i = 0; i < stateSize / sizeof(u32); i++)
		{
			state32[i] ^= key32[i];
		}
	}

	void A1CombineKey::inverse(u8* state, u32 stateSize, u8* key)
	{
		operate(state, stateSize, key);
	}
}