#include <CSV/Core/Reader.hpp>

#include <CSV/Utils.hpp>

#include <string>

namespace csv
{
	Reader::Reader(std::istream& input) :
		input(&input)
	{ }

	std::string Reader::read()
	{
		if (!continuable())
			throw std::exception("CSV Reader isn't continuable");

		if (buffer.length() == 0)
		{
			std::getline(*input, buffer);
			
			buffer += '\n';
		}

		if (buffer[0] == '\n')
		{
			buffer.erase(0, 1);

			return "\n";
		}

		const char* begin = buffer.c_str();
		const char* end = begin + buffer.length();

		const char* start = begin;

		for (; begin != end; begin++)
		{
			char current = *begin;

			if (current != ',' && current != '\n')
				continue;

			std::string cell(start, begin - start);

			trim(cell);

			buffer.erase(0, begin - start + (current == ','));

			return cell;
		}

		std::string cell = buffer;

		buffer.clear();

		return cell;
	}

	bool Reader::continuable()
	{
		return !input->eof();
	}
}