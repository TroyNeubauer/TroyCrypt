

#include <iostream>
#include <stdlib.h>
#include <string>
#include <memory>
#include <assert.h>
#include <stdio.h>
#include <Windows.h>
#include "boost/spirit.hpp"

#include "util/HardwareRNG.h"
#include "TroyCrypt.h"
#include "util/Utils.h"
#include "algorithms/A1/A1.h"

#include "parsing/parser.h"

#include <complex>


using namespace TroyCrypt;

int main() {

	std::cout << "/////////////////////////////////////////////////////////\n\n";
	std::cout << "\t\tA complex number micro parser for Spirit...\n\n";
	std::cout << "/////////////////////////////////////////////////////////\n\n";

	std::cout << "Give me a complex number of the form r or (r) or (r,i) \n";
	std::cout << "Type [q or Q] to quit\n\n";

	std::string str;
	while (getline(std::cin, str))
	{
		if (str.empty() || str[0] == 'q' || str[0] == 'Q')
			break;

		parse(str);
		
	}

	std::cout << "Bye... :-) \n\n";

#if 0
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
#endif
}
