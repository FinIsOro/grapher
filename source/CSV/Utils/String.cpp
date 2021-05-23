#include <CSV/Utils/String.hpp>

namespace csv
{
	void leftTrim(std::string& string)
	{
		string.erase(string.begin(), std::find_if(string.begin(), string.end(), [](unsigned char symbol) {
			return !std::isspace(symbol);
		}));
	}

	void rightTrim(std::string& string)
	{
		string.erase(std::find_if(string.rbegin(), string.rend(), [](unsigned char symbol) {
			return !std::isspace(symbol);
		}).base(), string.end());
	}

	void trim(std::string& string)
	{
		leftTrim(string);
		rightTrim(string);
	}
}
