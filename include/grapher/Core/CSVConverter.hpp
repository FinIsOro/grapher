#pragma once

#include <CSV/Core.hpp>
#include <Graph/Core.hpp>

namespace grapher
{
	class CSVConverter
	{
		bool continuable() const;
		
		void target(csv::Table& table);
		csv::Table& target();

		void reset();

		graph::Series next();

	private:
		csv::Table* _targer;

		std::vector<csv::Table::Area> areas;

		size_t row;
		size_t column;

		void skipAreas();
	};
}