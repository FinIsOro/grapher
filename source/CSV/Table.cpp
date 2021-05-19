#include <CSV/Table.hpp>

namespace csv
{
	Table::CellInfo* Table::at(unsigned int column, unsigned int row)
	{
		return cells[column][row];
	}

	void* Table::CellInfo::data()
	{
		return (void*)(parent->data.c_str() + position);
	}

	Table::CellInfo::Type Table::NumberCellInfo::type()
	{
		return Type::Number;
	}

	unsigned int Table::NumberCellInfo::size()
	{
		return sizeof(float);
	}

	Table::NumberCellInfo::NumberCellInfo(Table* parent, size_t position)
	{
		this->parent = parent;
		this->position = position;
	}

	Table::CellInfo::Type Table::StringCellInfo::type()
	{
		return Type::String;
	}
	unsigned int Table::StringCellInfo::size()
	{
		return length;
	}

	Table::StringCellInfo::StringCellInfo(Table* parent, size_t position, unsigned int length)
	{
		this->parent = parent;
		this->position = position;
		this->length = length;
	}

	Table::Builder::~Builder()
	{
		delete table;
	}

	void Table::Builder::reset()
	{
		column = 0;
		row = 0;

		delete table;

		table = new Table();
	}

	void Table::Builder::append(float value)
	{
		table->numberCells.push_back(NumberCellInfo(table, table->data.length()));
		table->cells[column++][row] = &table->numberCells.back();

		table->data.append((char*)&value, sizeof(float));
	}

	void Table::Builder::append(std::string value)
	{
		table->stringCells.push_back(StringCellInfo(table, table->data.length(), value.length()));
		table->cells[column++][row] = &table->stringCells.back();

		table->data += value;
	}

	void Table::Builder::line()
	{
		column = 0;
		row++;
	}

	Table& Table::Builder::build()
	{
		return *table;
	}
}