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
	u32 keyBytes;
	u8* key;
};

struct BlockContext : public TroyContext
{
	u32 blockSize;//AKA block size
	u8* state;
	//The current key derieved from the key schedule (or the same as key is no key schedule is specified)
	//Must be the same size as stateSize
	u8* subKey;
};

struct StreamContext : public TroyContext
{

};