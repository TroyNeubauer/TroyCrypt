
#include <string>
#include <iostream>
#include "BlockCipher.h"


namespace TroyCrypt {

void BlockCipher::encrypt(u8* plainText, u8* cipherText, u64 length, TroyContext* context) {
	BlockContext* c = dynamic_cast<BlockContext*>(context);
	if (c == nullptr) {
		throw std::string("Invalid context type in ").append(__FILE__).append("::").append(__func__).append(" line ").append(std::to_string(__LINE__));
	} else {
		encrypt_BlockCipher(plainText, cipherText, length, c);
	}
}
void BlockCipher::decrypt(u8* cipherText, u8* plainText, u64 length, TroyContext* context) {
	BlockContext* c = dynamic_cast<BlockContext*>(context);
	if (c == nullptr) {
		throw std::string("Invalid context type in ").append(__FILE__).append("::").append(__func__).append(" line ").append(std::to_string(__LINE__));
	} else {
		decrypt_BlockCipher(cipherText, plainText, length, c);
	}
}

}
