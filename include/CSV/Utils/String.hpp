#pragma once

#include <string>

namespace csv
{
	inline void leftTrim(std::string& string);
	inline void rightTrim(std::string& string);
	void trim(std::string& string);
}