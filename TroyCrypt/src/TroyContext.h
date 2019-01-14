#pragma once

#include "TroyCrypt.h"
/* Demo AES Program
name:AES128
block cipher
block size: 
key size: 128
key schedule:AES
impl:
combine key
9 rounds {
	subBytes("s_box.dat")
	shiftRows
	MixColumns
	combine key
}
subBytes("s_box.dat")
shiftRows
combine key


name:A1
block cipher
key size: 512
impl:
combine key
9 rounds {
	subBytes("s_box.dat")
	shiftRows
	MixColumns
	combine key
}
subBytes("s_box.dat")
shiftRows
combine key

*/
struct TroyContext
{
	//The origional key that is used for encryption and decryption
	TroyContext(u32 keyBytes);
	virtual ~TroyContext();

public:
	u32 const m_KeyBytes;
	u8* const m_Key;

	friend class BlockContext;
	friend class StreamContext;
};

struct BlockContext : TroyContext
{
	BlockContext(u32 blockBytes, u32 keyBytes, u32 rounds);
	virtual ~BlockContext();

public:
	//The same as subKeySize, can be different than keyBytes
	//The number of bytes in a single block
	u32 const m_BlockBytes;
	//The state
	u8* const m_State;
	//The current key derieved from the key schedule (or the same as key is no key schedule is specified)
	//Must be the same size as stateSize
	u8* const m_SubKey;
	//The number of rounds
	u32 const m_Rounds;

	//Non const members
	u32 m_RoundIteration = 0;

	//The current block we are working on
	u64 m_BlockIteration = 0;
	//The total number of blocks that will be operated on
	u64 m_TotalBlocks = 0;
	//Weather or not we are encrypting
	bool m_Encrypting = true;

};

struct StreamContext : TroyContext {

	virtual ~StreamContext();
};