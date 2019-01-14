#include "A1.h"


#define ROUND_COUNT 2

namespace TroyCrypt {
std::unique_ptr<BlockContext> A1::newContext() {
	return std::unique_ptr<BlockContext>(new BlockContext(A1_STATE_BYTES, A1_KEY_BYTES, ROUND_COUNT));
}

void A1::encryptBlock(BlockContext* context)
{
	context->m_RoundIteration = 0;
	for (int i = 0; i < ROUND_COUNT; i++, context->m_RoundIteration++)
	{
		keyCycle.nextKey(context);
		bitRotate.operate_BlockCipher(context);
		subBytes.operate_BlockCipher(context);
		combineKey.operate_BlockCipher(context);
	}
}

void A1::decryptBlock(BlockContext* context)
{
	context->m_RoundIteration = 0;
	for (int i = 0; i < ROUND_COUNT; i++, context->m_RoundIteration++)
	{
		keyCycle.nextKey(context);
		combineKey.inverse_BlockCipher(context);
		subBytes.inverse_BlockCipher(context);
		bitRotate.inverse_BlockCipher(context);
	}
}
}