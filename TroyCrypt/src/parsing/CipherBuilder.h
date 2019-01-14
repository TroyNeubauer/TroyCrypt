
#include <string>
#include <vector>

#include "../stage/CipherStage.h"
#include "../key/BlockKeySchedule.h"
#include "../cipher/TroyCipher.h"

namespace TroyCrypt {

#define DEFAULT_BLOCK_CIPHER_VALUE 2
#define DEFAULT_BLOCK_SIZE_VALUE -1
#define DEFAULT_KEY_SIZE_VALUE -1

class CipherBuilder {
	
public:
	TroyCipher* create(std::string& error);

	std::string name	= "";
	bool blockCipher	= DEFAULT_BLOCK_CIPHER_VALUE;
	int blockBytes		= DEFAULT_BLOCK_SIZE_VALUE;
	int keyBytes		= DEFAULT_KEY_SIZE_VALUE;
	BlockKeySchedule* keySchedule = nullptr;
	std::vector<CipherStage*> impl;
};
}
