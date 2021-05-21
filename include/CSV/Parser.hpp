#pragma once

#include <CSV/Table.hpp>

#include <string>

namespace csv
{
	class Parser
	{
	public:
		Table& table() const;

		void reset();

		Parser& operator<<(std::string chunk);
	
	private:
		Table::Builder builder;
		std::string buffer;
	};
}