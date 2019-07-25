

#include <iostream>
#include <stdlib.h>
#include <string>
#include <memory>
#include <assert.h>
#include <stdio.h>
#include <Windows.h>
#include <ctime>

#include "util/HardwareRNG.h"
#include "TroyCrypt.h"
#include "util/Utils.h"
#include "algorithms/A1/A1.h"

#include "analysis/CryptAnalysis.h"


using namespace TroyCrypt;

int main() {
#if 0
	std::unique_ptr<BlockContext> context = A1::newContext();
	u64 length = 1000;
	HardwareRNG rng;
	u8 test[32];
	rng.getBytes(test, sizeof(test));
	std::cout << std::hex;
	for (int i = 0; i < sizeof(test); i++) {
		std::cout << "0x" << (int) test[i] << ", ";
	}
	system("PAUSE");

	rng.getBytes(context->m_Key, context->m_KeyBytes);

	length = padToStateSize(A1_STATE_BYTES, length);
	std::unique_ptr<u8[]> plainTextA1(new u8[length]());
	std::unique_ptr<u8[]> cipherTextA1(new u8[length]());
	A1 a1;
	DiffusionResult shannon = doDiffusionAnalysis(plainTextA1.get(), cipherTextA1.get(), length, context.get(), (TroyCipher*) &a1);
	FrequencyResult frequency = doFrequencyAnalysis(plainTextA1.get(), cipherTextA1.get(), length, context.get(), (TroyCipher*) &a1, 1000);
	std::cout << shannon;
	std::cout << frequency;
	system("PAUSE");
#else
	std::unique_ptr<BlockContext> context = A1::newContext();

	HardwareRNG rng;

	A1 a1;
	u64 length = padToStateSize(A1_STATE_BYTES, A1_KEY_BYTES * 10);//Plaintext and cipher text length
	u8* data = new u8[A1_KEY_BYTES]();

	
	std::unique_ptr<u8[]> cipherText(new u8[length]());
	std::unique_ptr<u8[]> decrypted (new u8[length]());
	std::unique_ptr<u8[]> plainText = padBufferToStateSize(data, length, A1_STATE_BYTES);

	rng.getBytes(context->m_Key, A1_KEY_BYTES);
	std::cout << "Key:" << std::endl;
	hex_dump(context->m_Key, A1_KEY_BYTES);
	memcpy(context->m_SubKey, context->m_Key, context->m_KeyBytes);

	DiffusionResult shannon = doDiffusionAnalysis(plainText.get(), cipherText.get(), length, context.get(), (TroyCipher*)& a1);
	FrequencyResult frequency = doFrequencyAnalysis(plainText.get(), cipherText.get(), length, context.get(), (TroyCipher*)& a1, 1000);
	std::cout << shannon << std::endl;
	std::cout << frequency << std::endl;


	/*std::cout << "Origional" << std::endl;
	hex_dump(plainText.get(), length);

	a1.encrypt_BlockCipher(plainText.get(), cipherText.get(), length, context.get());
	std::cout << "Encrypted" << std::endl;
	hex_dump(cipherText.get(), length);

	a1.decrypt_BlockCipher(cipherText.get(), decrypted.get(), length, context.get());
	std::cout << "Decrypted" << std::endl;
	hex_dump(decrypted.get(), length);

	std::cout << std::endl << "Plaintext equals decrypted: " << buffersEqual(plainText.get(), decrypted.get(), length) << std::endl;*/

	system("PAUSE");
#endif
	return 0;
}
