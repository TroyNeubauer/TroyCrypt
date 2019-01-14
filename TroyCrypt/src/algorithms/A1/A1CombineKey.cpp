#include "A1CombineKey.h"
#include "../../util/Utils.h"
#include "../../util/Utils.h"

namespace TroyCrypt {

void A1CombineKey::operate_BlockCipher(BlockContext* context)
{
	u64* state64 = (u64*) context->m_State;
	u64* key64 = (u64*) context->m_SubKey;

	for (int i = 0; i < context->m_BlockBytes / sizeof(u64); i++)
	{
		state64[i] ^= key64[i];
	}
}

void A1CombineKey::inverse_BlockCipher(BlockContext* context)
{
	operate_BlockCipher(context);
}
}