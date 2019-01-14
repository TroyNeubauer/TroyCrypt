
#include "../cipher/StockBlockCipher.h"
#include "aes.hpp"

#define AES256_BLOCK_BYTES (4*4)
#define AES256_KEY_BYTES (256 / 8)
#define AES256_ROUNDS 14

namespace TroyCrypt {

class AES256 : public BlockCipher {
	AES256();
	void encrypt_BlockCipher(u8* plainText, u8* cipherText, u64 length, BlockContext* context);
	void decrypt_BlockCipher(u8* cipherText, u8* plainText, u64 length, BlockContext* context);

	static std::unique_ptr<BlockContext> newContext();
private:
	AES_ctx aes_ctx;
	u8 iv[AES256_KEY_BYTES] = {};
};


}