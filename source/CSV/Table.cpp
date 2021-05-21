#include <CSV/Table.hpp>

namespace csv
{
	Table::CellInfo* Table::at(size_t column, size_t row) const
	{
		if (cells.find(column) == cells.end())
			return nullptr;

		auto& rows = cells.at(column);

		if (rows.find(row) == rows.end())
			return nullptr;

		return rows.at(row);
	}

	Table::Table()
	{ }

	Table::Size Table::volume() const
	{
		return size;
	}

	Table::Size::Size(size_t columns, size_t rows) :
		columns(columns), rows(rows)
	{ }

	Table::Bound::Bound(Range column, Range row) :
		column(column), row(row)
	{ }

	bool Table::Bound::include(size_t column, size_t row) const
	{
		return this->column.include(column) && this->row.include(row);
	}

	bool Table::Bound::outclude(size_t column, size_t row) const
	{
		return this->column.outclude(column) || this->row.outclude(row);
	}

	Table::Size Table::Bound::size() const
	{
		return Size(column.size(), row.size());
	}

	Table::Bound::Range::Range(size_t start, size_t end) :
		start(start), end(end)
	{ }

	inline bool Table::Bound::Range::include(size_t value) const
	{
		return value >= start && value <= end;
	}

	inline bool Table::Bound::Range::outclude(size_t value) const
	{
		return value < start || value > end;
	}

	size_t Table::Bound::Range::size() const
	{
		return end - start;
	}

	void* Table::CellInfo::data() const
	{
		return (void*)(parent->data.c_str() + position);
	}

	size_t Table::CellInfo::size() const
	{
		return 0;
	}

	Table::CellInfo::Type Table::NumberCellInfo::type() const
	{
		return Type::Number;
	}

	size_t Table::NumberCellInfo::size() const
	{
		return sizeof(float);
	}

	Table::NumberCellInfo::NumberCellInfo(Table* parent, size_t position)
	{
		this->parent = parent;
		this->position = position;
	}

	Table::CellInfo::Type Table::StringCellInfo::type() const
	{
		return Type::String;
	}

	size_t Table::StringCellInfo::size() const
	{
		return length;
	}

	Table::StringCellInfo::StringCellInfo(Table* parent, size_t position, size_t length)
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
		table->size.columns = std::max(table->size.columns, column);
		table->size.rows = row + 1;
	}

	void Table::Builder::line()
	{
		table->size.columns = std::max(table->size.columns, column);
	
		column = 0;
		row++;
	}

	Table& Table::Builder::build() const
	{
		return *table;
	}
}