#include <Grapher/Util/Number.hpp>

#include <math.h>

namespace grapher
{
	inline bool Number::digit(char value)
	{
		return value >= '0' && value <= '9';
	}

	inline bool Number::dot(char value)
	{
		return value == '.' || value == ',';
	}

	bool Number::parse(const char* data, size_t length, int& out)
	{
		int result = 0;

		bool negative = *data == '-';
		bool positive = *data == '+';

		const char* end = data + length;

		if (negative || positive)
			data++;

		for (; data != end; data++)
			if (digit(*data))
				result = result * 10 + *data - '0';
			else
				return false;

		out = negative ? -result : result;

		return true;
	}

	bool Number::parse(const char* data, size_t length, float& out)
	{
		if (length == 0)
			return false;
		
		float result = 0;
		float rank = 1;

		bool dotted = false;
		bool negative = *data == '-';
		bool positive = *data == '+';

		int exponent = 1;

		const char* end = data + length;

		if (negative || positive)
			data++;

		for (; data != end; data++)
			if (digit(*data))
				result = dotted
					? rank *= .1f, result + (*data - '0') * (rank)
					: result * 10 + *data - '0';
			else if (dot(*data))
				if (!dotted)
					dotted = true;
				else
					return false;
			else if (*data == 'E' || *data == 'e')
			{
				data++;

				if (parse(data, end - data, exponent))
					break;
				else
					return false;
			}
			else
				return false;

		out = negative ? -result : result;

		if (exponent != 1)
			out = pow(out, exponent);

		return true;
	}
}
