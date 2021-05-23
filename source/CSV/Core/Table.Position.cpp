#include <CSV/Core/Table.hpp>

namespace csv
{
	Table::Position::Position(size_t column, size_t row) :
		column(column), row(row)
	{ }

	void Table::Position::reset()
	{
		column = 0;
		row = 0;
	}

	void Table::Position::set(size_t column, size_t row)
	{
		this->column = column;
		this->row = row;
	}
}