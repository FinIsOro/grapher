#pragma once

#include <CSV/Core.hpp>
#include <Graph/Core.hpp>

namespace grapher
{
	class CSVConverter
	{
	public:
		CSVConverter(csv::Table& table);
		CSVConverter() = default;

		bool continuable();
		
		void target(csv::Table& table);
		csv::Table& target();

		void reset();

		graph::Series& next();

	private:
		csv::Table* _target;
		csv::Table::Position position;

		graph::Series current;

		std::vector<csv::Table::Area> areas;

		std::vector<csv::Table::Area>::iterator insideArea();
		void skipAreas();
	};
}