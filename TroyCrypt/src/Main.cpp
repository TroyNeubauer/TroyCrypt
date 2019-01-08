#include "algorithms/A1/A1.h"
#include "util/Utils.h"
#include "TroyCrypt.h"

#include "util/HardwareRNG.h"

#include <iostream>
#include <stdlib.h>
#include <string>
#include <memory>
#include <assert.h>
#include <stdio.h>
#include <Windows.h>
#include "boost/spirit.hpp"

int main() {
	std::cout << "Hello World" << std::endl;
}


using namespace TroyCrypt;
#if 0
int main() {

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, 1000, 550, true);

	HardwareRNG rng;
	const uint32_t bytes = A1_KEY_BYTES;
	u8* key = new u8[bytes];
	rng.getBytes(key, bytes);

	hex_dump(std::cout, key, bytes);

	A1 a1;
	u8* data = new u8[510]();
	u64 length = padToStateSize(a1.getStateSize(), 510);
	
	std::unique_ptr<u8[]> cipherText(new u8[length]);
	std::unique_ptr<u8[]> decrypted (new u8[length]);
	std::unique_ptr<u8[]> plainText = padBufferToStateSize(data, 510, a1.getStateSize());

	std::cout << "Origional" << std::endl;
	hex_dump(std::cout, plainText.get(), length);

	a1.encrypt(plainText.get(), cipherText.get(), length, key);
	std::cout << "Encrypted" << std::endl;
	hex_dump(std::cout, cipherText.get(), length);

	a1.decrypt(cipherText.get(), decrypted.get(), length, key);
	std::cout << "Decrypted" << std::endl;
	hex_dump(std::cout, decrypted.get(), length);

	std::cout << std::endl << "Plaintext equals decrypted: " << buffersEqual(plainText.get(), decrypted.get(), length) << std::endl;

	system("PAUSE");

}


#endif