

#include "A1KeyCycle.h"
#include <iostream>
#include "../../util/Utils.h"

namespace TroyCrypt {

void A1KeyCycle::nextKey(BlockContext* context) {
	memcpy((u8*) context->m_SubKey, context->m_Key, context->m_KeyBytes);

	u64* subKey = (u64*) context->m_SubKey;
	for (int i = 0; i < context->m_BlockBytes / sizeof(u64); i++)
	{
		//Make sure to go in reverse order when decrypting
		int rotateBits = context->m_BlockIteration * context->m_Rounds;
		rotateBits += context->m_Encrypting ? (context->m_RoundIteration) : (context->m_Rounds - context->m_RoundIteration - 1);
			
		subKey[i] = _rotr64(subKey[i], rotateBits);
	}
}
}