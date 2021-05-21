#include <Grapher/Converters/CSVToSeries.hpp>

using namespace csv;
using namespace std;

namespace grapher::converters
{
	std::vector<Series> grapher::converters::CSVToSeries::convert(const Table& table)
	{
		std::vector<Series> result;

		vector<Table::Bound> bounds;
		Table::Bound currentBound;

		auto tableSize = table.volume();

		for (size_t row = 0; row < tableSize.rows; row++)
			for (size_t column = 0; column < tableSize.columns; column++)
			{
				for (auto& bound : bounds)
					if (bound.include(column, row))
						goto end;

				{
					auto cellInfo = table.at(column, row);

					if (cellInfo == nullptr || cellInfo->type() != Table::CellInfo::Type::Number)
						continue;

					currentBound.column.start = column;
					currentBound.row.start = row;

					row++;

					for (; row < tableSize.rows; row++)
					{
						auto cellInfo = table.at(column, row);

						if (cellInfo != nullptr && cellInfo->type() == Table::CellInfo::Type::Number && row != static_cast<unsigned long long>(tableSize.rows) - 1)
							continue;

						currentBound.row.end = row;

						unsigned short findedNubmers;

						column++;

						for (; column < tableSize.columns; column++)
						{
							findedNubmers = 0;

							for (row = currentBound.row.start; row < currentBound.row.end; row++)
							{
								auto cellInfo = table.at(column, row);

								findedNubmers += cellInfo != nullptr && cellInfo->type() == Table::CellInfo::Type::Number;

								if (findedNubmers == 2)
									break;
							}

							if (findedNubmers == 2 && column != static_cast<unsigned long long>(tableSize.columns) - 1)
								continue;

							currentBound.column.end = column - (findedNubmers != 2);

							break;
						}

						break;
					}

					column = currentBound.column.end;
					row = currentBound.row.start;

					bounds.push_back(currentBound);
				}

			end:

				int a = 2 + 2;
			}

		for (auto& bound : bounds)
		{
			Series series;

			size_t rangesAmount = bound.column.size();

			for (size_t rangeIndex = 0; rangeIndex < rangesAmount; rangeIndex++)
			{
				std::string name;

				if (bound.row.start != 0)
				{
					auto cellInfo = table.at(bound.column.start + rangeIndex + 1, bound.row.start - 1);

					if (cellInfo != nullptr && cellInfo->type() == Table::CellInfo::Type::String)
						name = std::string((const char*)cellInfo->data(), cellInfo->size());
				}

				series.ranges.add(name);
			}

			for (size_t row = bound.row.start; row <= bound.row.end; row++)
			{
				float key = *(float*)table.at(bound.column.start, row)->data();
				std::vector<float> values;

				for (size_t column = static_cast<size_t>(bound.column.start) + 1; column <= bound.column.end; column++)
				{
					auto cellInfo = table.at(column, row);

					values.push_back(cellInfo != nullptr && cellInfo->type() == Table::CellInfo::Type::Number
						? *(float*)cellInfo->data()
						: NAN);
				}

				series.add(key, values);
			}

			result.push_back(series);
		}

		return result;
	}
}