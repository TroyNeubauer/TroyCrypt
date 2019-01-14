#include "CipherBuilder.h"
#include <sstream>


namespace TroyCrypt {
TroyCipher* CipherBuilder::create(std::string& error) {
	std::stringstream ss;
	TroyCipher* result = nullptr;
	if (name.length() == 0) {
		ss << "No cipher name given" << std::endl;
	} 
	if (impl.size() == 0) {
		ss << "No cipher implementation provided" << std::endl;
	} 
	if (blockCipher == DEFAULT_BLOCK_CIPHER_VALUE) {
		ss << "A cipher must be defined as a block cipher" << std::endl;
	}
	if (blockCipher) {
		if (blockBytes == DEFAULT_BLOCK_SIZE_VALUE) {
			ss << "No block size provided" << std::endl;
		}
		if (keyBytes == DEFAULT_KEY_SIZE_VALUE) {
			ss << "No key size provided" << std::endl;
		}
		if (keySchedule == nullptr) {
			ss << "No key schedule provided" << std::endl;
		}

	} else {
		ss << "Only block ciphers are currently supported" << std::endl;
	}

	std::string tempError = ss.str();
	if (tempError.length() > 0) {
		error = tempError;
		return nullptr;
	}
	return result;
}
}