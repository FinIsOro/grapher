#include "..\..\..\include\CSV\Core\Writer.hpp"

namespace csv
{
	Writer::Writer(std::ostream& output) :
		output(&output)
	{ }

	void Writer::write(std::string data)
	{
		if (first)
			output->write(",", 1);

		output->write(data.c_str(), data.length());

		first = data.back() == '\n';
	}
}