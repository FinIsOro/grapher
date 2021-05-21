#pragma once

#include <CSV/Table.hpp>
#include <Grapher/Series.hpp>

namespace grapher::converters
{
	class CSVToSeries
	{
	public:
		static std::vector<Series> convert(const csv::Table& table);
	};
}