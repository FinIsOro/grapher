#include <Grapher/Core/CSVConverter.hpp>

#include <Grapher/Util/Number.hpp>

using namespace csv;
using namespace graph;
using namespace std;

namespace grapher
{
	CSVConverter::CSVConverter(csv::Table& table) :
		_target(&table)
	{ }

	bool CSVConverter::continuable()
	{
		auto targetSize = _target->size();

		skipAreas();

		while (position.column != -1)
		{
			auto cell = _target->get(position.column, position.row);

			float number;

			if (Number::parse(cell.c_str(), cell.length(), number))
				break;

			if (++position.column == targetSize.columns)
				position.set(0, position.row + 1);

			skipAreas();
		}

		return position.column != -1;
	}

	void CSVConverter::target(Table& table)
	{
		_target = &table;
	}

	Table& CSVConverter::target()
	{
		return *_target;
	}

	void CSVConverter::reset()
	{
		position.set(0, 0);
		current.clear();
		areas.clear();
	}

	Series& CSVConverter::next()
	{
		if (!continuable())
			throw exception("CSVConverter is not continuable");

		current.clear();

		vector<float> domain;
		vector<vector<float>> ranges;
		vector<string> rangeNames;

		Table::Area area({ position.column }, { position.row });

		auto targetSize = _target->size();

		float number;

		string cell;

		while (
			position.row != targetSize.rows &&
			(
				cell = _target->get(position.column, position.row++),
				Number::parse(cell.c_str(), cell.length(), number)
			)
		)
			domain.push_back(number);

		area.row.end = position.row - 1;

		position.set(area.column.start + 1, area.row.start);

		size_t endRowIndex = area.row.end + 1;
		size_t domainSize = domain.size();

		while (position.column != targetSize.columns)
		{
			ranges.push_back({ });

			auto& range = ranges.back();

			range.resize(domainSize, NAN);

			bool numberFound = false;

			for (; position.row != endRowIndex; position.row++)
				if (
					cell = _target->get(position.column, position.row),
					Number::parse(cell.c_str(), cell.length(), number)
					)
					numberFound = true,
					range[position.row - area.row.start] = number;

			if (!numberFound)
			{
				ranges.pop_back();

				break;
			}
			
			rangeNames.push_back(area.row.start != 0
				? _target->get(position.column, area.row.start - 1)
				: "");

			position.column++;
			position.row = area.row.start;
		}

		area.column.end = position.column - 1;

		areas.push_back(area);

		position.set(area.column.end, area.row.start);

		size_t rangesAmount = ranges.size();

		current.addRanges(rangesAmount);

		size_t rangeIndex = 0;

		for (auto& range : current.ranges())
			range.name = rangeNames[rangeIndex++];

		for (size_t domainIndex = 0; domainIndex < domainSize; domainIndex++)
		{
			vector<float> values;

			values.resize(rangesAmount);

			for (size_t rangeIndex = 0; rangeIndex < rangesAmount; rangeIndex++)
				values[rangeIndex] = ranges[rangeIndex][domainIndex];

			current.push(domain[domainIndex], values);
		}
		
		return current;
	}

	vector<Table::Area>::iterator CSVConverter::insideArea()
	{
		auto areasIterator = areas.begin();
		auto areasEnd = areas.end();

		for (; areasIterator != areasEnd; ++areasIterator)
			if (areasIterator->include(position.column, position.row))
				break;

		return areasIterator;
	}
	
	void CSVConverter::skipAreas()
	{
		const auto& areasEnd = areas.end();
		auto targetSize = _target->size();

		auto area = insideArea();

		while (area != areasEnd)
		{
			if (area->column.end == targetSize.columns - 1)
				if (area->include(0, position.row + 1))
					if (area->row.end == targetSize.rows - 1)
					{
						position.set(-1, -1);

						break;
					}
					else
						position.set(0, area->row.end + 1);
				else
					if (position.row == targetSize.rows - 1)
					{
						position.set(-1, -1);

						break;
					}
					else
						position.set(0, position.row + 1);
			else
				position.column = area->column.end + 1;

			area = insideArea();
		}
	}
}