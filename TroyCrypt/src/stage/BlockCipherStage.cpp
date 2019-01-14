
#include "BlockCipherStage.h"
#include <string>

namespace TroyCrypt {

void BlockCipherStage::operate(TroyContext* context) {
	BlockContext* c = dynamic_cast<BlockContext*>(context);
	if (c == nullptr) {
		throw std::string("Invalid context type in ").append(__FILE__).append("::").append(__func__).append(" line ").append(std::to_string(__LINE__));
	}
	else {
		operate_BlockCipher(c);
	}
}
void BlockCipherStage::inverse(TroyContext* context) {
	BlockContext* c = dynamic_cast<BlockContext*>(context);
	if (c == nullptr) {
		throw std::string("Invalid context type in ").append(__FILE__).append("::").append(__func__).append(" line ").append(std::to_string(__LINE__));
	}
	else {
		inverse_BlockCipher(c);
	}
}

}
