#include "A1Circular64BitShift.h"
#include <intrin.h>
#include <immintrin.h>


namespace TroyCrypt {

void A1Circular64BitShift::operate_BlockCipher(BlockContext* context)
{
	u64* state64 = (u64*) context->m_State;
	for (int i = 0; i < context->m_BlockBytes / sizeof(u64); i++)
	{
		state64[i] = _rotr64(state64[i], 11);
	}
}

void A1Circular64BitShift::inverse_BlockCipher(BlockContext* context)
{
	u64* state64 = (u64*) context->m_State;
	for (int i = 0; i < context->m_BlockBytes / sizeof(u64); i++)
	{
		state64[i] = _rotl64(state64[i], 11);
	}
}
}
