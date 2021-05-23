#pragma once

#include <istream>

namespace csv
{
	class Reader
	{
	public:
		Reader(std::istream& input);

		inline bool continuable();

		std::string read();

	private:
		std::istream* input;
		std::string buffer;
	};
}