#include "DynamicBlockCipher.h"

namespace TroyCrypt {

	DynamicBlockCipher::DynamicBlockCipher(u32 stateSize)
	{
		m_StateSize = stateSize;
		m_State = new u8[stateSize];
	}

	u32 DynamicBlockCipher::getStateSize() { return m_StateSize; }
	u8* DynamicBlockCipher::getState() { return m_State; }

	DynamicBlockCipher::~DynamicBlockCipher()
	{
		delete[] m_State;
	}
}