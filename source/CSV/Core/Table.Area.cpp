#include <CSV/Core/Table.hpp>

namespace csv
{
	Table::Area::Area(csv::Range column, csv::Range row) :
		column(column), row(row)
	{ }

	bool Table::Area::include(size_t column, size_t row) const
	{
		return this->column.include(column) && this->row.include(row);
	}

	bool Table::Area::outclude(size_t column, size_t row) const
	{
		return this->column.outclude(column) || this->row.outclude(row);
	}

	Table::Size Table::Area::size() const
	{
		return Size(column.size(), row.size());
	}
}

