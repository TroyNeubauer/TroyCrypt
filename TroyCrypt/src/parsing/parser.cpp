

#include "parser.h"
#include "../algorithms/A1/A1.h"

namespace TroyCrypt {

TroyCipher* parseString(std::string text) {
	A1* c = new A1();
	double d = 0.0;

	memory_input<> in(text, "std::cin");
	if (parse< parser::grammar, parser::action >(in, d, "TEST")) {
		std::cout << "parsing OK; sum = " << d << std::endl;
	} else {
		std::cout << "parsing failed" << std::endl;
	}

	return (TroyCipher*) c;
}

}