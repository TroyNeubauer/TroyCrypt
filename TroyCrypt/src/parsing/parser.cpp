
#include "parser.h"
#include "../algorithms/A1/A1.h"

#define BOOST_SPIRIT_USE_PHOENIX_V3
#define BOOST_RESULT_OF_USE_DECLTYPE
#include <boost/spirit/include/classic.hpp>


/*=============================================================================
	Copyright (c) 2002-2010 Joel de Guzman
	Distributed under the Boost Software License, Version 1.0. (See accompanying
	file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  A complex number micro parser.
//
//  [ JDG May 10, 2002 ]    spirit1
//  [ JDG May 9, 2007 ]     spirit2
//
///////////////////////////////////////////////////////////////////////////////

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <iostream>
#include <string>
#include <complex>

///////////////////////////////////////////////////////////////////////////////
//  Our complex number parser/compiler
///////////////////////////////////////////////////////////////////////////////
//[tutorial_complex_number
namespace client
{

	void func(double d) {
		std::cout << "Got called! " << d << std::endl;
	}
	template <typename Iterator>
	bool parse_complex(Iterator first, Iterator last, std::complex<double>& c)
	{
		using boost::spirit::qi::double_;
		using boost::spirit::qi::_1;
		using boost::spirit::qi::phrase_parse;
		using boost::spirit::ascii::space;
		using boost::phoenix::ref;

		bool r = phrase_parse(first, last, (
				'(' >> double_[func] >> -(',' >> double_[func]) >> ')' | double_[func]
				), space);

		if (!r || first != last) // fail if we did not get a full match
			return false;
		c = std::complex<double>(rN, iN);
		return r;
	}
}


namespace TroyCrypt {

	TroyCipher* parse(std::string text) {
		A1* c = new A1();
		std::complex<double> d;
		if (client::parse_complex(text.begin(), text.end(), d)) {
			std::cout << "-------------------------\n";
			std::cout << "Parsing succeeded\n";
			std::cout << "got: " << d << std::endl;
			std::cout << "\n-------------------------\n";
			return (TroyCipher*) c;
		}
		else
		{
			std::cout << "-------------------------\n";
			std::cout << "Parsing failed\n";
			std::cout << "-------------------------\n";
			return nullptr;
		}

	}

}