
#include "TroyContext.h"

TroyContext::TroyContext(u32 keyBytes) 
	: m_KeyBytes(keyBytes), m_Key(new u8[keyBytes]()) {}

TroyContext::~TroyContext() {
	delete[] m_Key;
}

BlockContext::BlockContext(u32 blockBytes, u32 keyBytes, u32 rounds) 
	: TroyContext(keyBytes), m_Rounds(rounds), m_BlockBytes(blockBytes),
	m_State(new u8[blockBytes]()), m_SubKey(new u8[keyBytes]()) {}

BlockContext::~BlockContext() {
	delete[] m_State;
	delete[] m_SubKey;
}

StreamContext::~StreamContext() {

}