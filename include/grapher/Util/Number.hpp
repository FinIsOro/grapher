#pragma once

namespace grapher
{
	class Number
	{
	public:
		inline static bool digit(char value);
		inline static bool dot(char value);

		static bool parse(const char* data, size_t length, int& out);
		static bool parse(const char* data, size_t length, float& out);
	};
}