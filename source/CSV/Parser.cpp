#include <CSV/Parser.hpp>

bool parseFloat(const char* data, size_t length, float& out)
{
	float result = 0;
	float power = 1;

	for (size_t index = 0; index < length; index++)
	{
		if (data[index] >= '0' && data[index] <= '9')
			if (power == 1)
				result = result * 10 + data[index] - '0';
			else
			{
				result += (data[index] - '0') * (power);
				power *= .1f;
			}
		else if (data[index] == '.' || data[index] == ',')
			if (power == 1)
				power = .1f;
			else
				return false;
		else
			return false;
	}

	out = result;

	return true;
}

namespace csv
{
	Table& Parser::table()
	{
		return builder.build();
	}

	void Parser::reset()
	{
		builder.reset();
	}

	Parser& Parser::operator<<(std::string chunk)
	{
		buffer += chunk;

		const char* begin = buffer.c_str();
		const char* end = begin + buffer.length();
		
		const char* start = begin;

		for (; begin != end; begin++)
		{
			char current = *begin;

			if (current == ',' || current == '\n')
			{
				float number;

				if (parseFloat(start, begin - start, number))
					builder.append(number);
				else
					builder.append(std::string(start, begin - start));

				start = begin + 1;

				if (current == '\n')
					builder.line();
			}
		}

		if (start != begin + 1)
			buffer = std::string(start, end - start);

		return *this;
	}
}