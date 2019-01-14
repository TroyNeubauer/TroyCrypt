

#include "AES256.h"
#include "../util/Utils.h"
#include "../util/HardwareRNG.h"

namespace TroyCrypt {

	AES256::AES256() {
		HardwareRNG rng;
		
	}
std::unique_ptr<BlockContext> AES256::newContext() {
	return std::unique_ptr<BlockContext>(new BlockContext(AES256_BLOCK_BYTES, AES256_KEY_BYTES, AES256_ROUNDS));
}

void AES256::encrypt_BlockCipher(u8* plainText, u8* cipherText, u64 length, BlockContext* context) {
	AES_init_ctx_iv(&aes_ctx, context->m_Key, iv);
	AES_CBC_encrypt_buffer(&aes_ctx, cipherText, (unsigned int) length);
}
void AES256::decrypt_BlockCipher(u8* cipherText, u8* plainText, u64 length, BlockContext* context) {

}

}