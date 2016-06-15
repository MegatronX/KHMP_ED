#pragma once
#ifndef _BOOSTOVERRIDES_H_
#define _BOOSTOVERRIDES_H_
#include <boost/lexical_cast.hpp>

namespace boost {
	template<>
	inline bool lexical_cast<bool, std::string>(const std::string& arg) {
		std::istringstream ss(arg);
		bool b;
		ss >> std::boolalpha >> b;
		return b;
	}

	template<>
	inline std::string lexical_cast<std::string, bool>(const bool& b) {
		std::ostringstream ss;
		ss << std::boolalpha << b;
		return ss.str();
	}
}

#endif