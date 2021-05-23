#pragma once

#include <ostream>

namespace csv
{
	class Writer
	{
	public:
		Writer(std::ostream& output);

		void write(std::string data = "\n");

	private:
		std::ostream* output;
		bool first = true;
	};
}