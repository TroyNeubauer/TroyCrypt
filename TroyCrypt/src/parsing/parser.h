
#include "../cipher/TroyCipher.h"
#include <string>

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

#include <tao/pegtl.hpp>

using namespace tao::TAO_PEGTL_NAMESPACE;  // NOLINT

#include <tao/pegtl.hpp>

namespace double_
{
// A grammar for doubles suitable for std::stod without locale support.
// See also: http://en.cppreference.com/w/cpp/string/basic_string/stof

using namespace tao::TAO_PEGTL_NAMESPACE;  // NOLINT

// clang-format off
struct plus_minus : opt< one< '+', '-' > > {};
struct dot : one< '.' > {};

struct inf : seq< istring< 'i', 'n', 'f' >,
	opt< istring< 'i', 'n', 'i', 't', 'y' > > > {};

struct nan : istring< 'n', 'a', 'n' > {};

template< typename D >
struct number : if_then_else< dot,
	plus< D >,
	seq< plus< D >, opt< dot, star< D > > > > {};

struct e : one< 'e', 'E' > {};
struct p : one< 'p', 'P' > {};
struct exponent : seq< plus_minus, plus< digit > > {};

struct decimal : seq< number< digit >, opt< e, exponent > > {};
struct hexadecimal : seq< one< '0' >, one< 'x', 'X' >, number< xdigit >, opt< p, exponent > > {};

struct grammar : seq< plus_minus, sor< hexadecimal, decimal, inf, nan > > {};


}// namespace double_


namespace parser
{
struct padded_double
	: pad< double_::grammar, blank >
{
};

struct double_list
	: list< padded_double, one< ',' > >
{
};

struct grammar
	: seq< double_list, eof >
{
};

template< typename Rule >
struct action
	: nothing< Rule >
{
};


template<>
struct action< double_::grammar >
{
	template< typename Input >
	static void apply(const Input& in, double& sum, std::string s)
	{
		std::cout << "Test! " << s << std::endl;
		std::stringstream ss;
		ss << in.string();
		double v;
		ss >> v;
		sum += v;
	}
};
}  // namespace sum


namespace TroyCrypt {

TroyCipher* parseString(std::string text);

}