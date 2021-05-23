#include <CSV/Core/Table.hpp>

#include <stdexcept>

namespace csv
{
	Table::Size Table::size()
	{
		return _size;
	}

	std::string Table::get(size_t column, size_t row)
	{
		checkSize(column, row);

		if (column >= _size.columns)
			throw std::out_of_range("column index out of range");

		if (row >= _size.rows)
			throw std::out_of_range("row index out of range");

		if (column == _size.columns - 1)
			return std::string(rows[row].c_str() + pointers[column][row]);
		
		return std::string(rows[row].c_str() + pointers[column][row], pointers[column + 1][row] - pointers[column][row]);
	}

	void Table::set(size_t column, size_t row, std::string value)
	{
		checkSize(column, row);

		auto& rowData = rows[row];

		size_t cellPosition = pointers[column][row];
		size_t cellSize = column == _size.columns - 1
			? rowData.length() - cellPosition
			: pointers[column + 1][row] - pointers[column][row];

		rowData.replace(cellPosition, cellSize, value);

		long long deltaSize = value.length() - cellSize;

		if (deltaSize != 0)
		{
			column++;

			for (; column < _size.columns; column++)
				pointers[column][row] += deltaSize;
		}
	}

	void Table::resize(size_t columns, size_t rows)
	{
		if (columns < _size.columns)
			popColumns(_size.columns - columns);
		else if (columns > _size.columns)
			pushColumns(columns - _size.columns);

		if (rows < _size.rows)
			popRows(_size.rows - rows);
		else if (rows > _size.rows)
			pushRows(rows - _size.rows);
	}

	void Table::insertColumn(size_t index)
	{
		checkColumnInsertion(index);

		if (index == _size.columns)
			return pushColumn();
		else if (index == 0)
			return unshiftColumn();

		auto& nextColumnPointers = pointers[index];

		pointers.insert(pointers.begin() + index, std::vector<size_t>());

		auto& columnPointers = pointers[index];

		for (size_t row = 0; row < _size.rows; row++)
			columnPointers.push_back(nextColumnPointers[row]);

		_size.columns++;

		if (_size.rows == 0)
			_size.rows = 1;
	}
	
	void Table::insertRow(size_t index)
	{
		checkRowsInsertion(index);

		if (index == _size.rows)
			return pushRow();
		else if (index == 0)
			return unshiftRow();

		rows.insert(rows.begin() + index, std::string());

		for (size_t column = 0; column < _size.columns; column++)
		{
			auto& columnPointers = pointers[column];

			columnPointers.insert(columnPointers.begin() + index, 0);
		}

		_size.rows++;

		if (_size.columns == 0)
			_size.columns = 1;
	}
	
	void Table::insertColumns(size_t index, size_t amount)
	{
		checkColumnInsertion(index);

		if (index == _size.columns)
			return pushColumns(amount);
		else if (index == 0)
			return unshiftColumns(amount);

		for (; amount != 0; amount--)
			insertColumn(index);
	}
	
	void Table::insertRows(size_t index, size_t amount)
	{
		checkRowsInsertion(index);

		if (index == _size.rows)
			return pushRows(amount);
		else if (index == 0)
			return unshiftRows(amount);

		for (; amount != 0; amount--)
			insertRow(index);
	}
	
	void Table::pushColumn()
	{
		if (_size.columns == 0)
			pointers.push_back({ 0 });
		else
		{
			pointers.push_back(std::vector<size_t>());

			auto& lastColumnPointers = pointers.back();

			for (size_t row = 0; row < _size.rows; row++)
				lastColumnPointers.push_back(rows[row].length());
		}

		_size.columns++;

		if (_size.rows == 0)
		{
			rows.push_back(std::string());

			_size.rows = 1;
		}
	}
	
	void Table::pushRow()
	{
		rows.push_back(std::string());

		for (size_t column = 0; column < _size.columns; column++)
		{
			auto& columnPointers = pointers[column];

			columnPointers.push_back(columnPointers.back());
		}

		_size.rows++;

		if (_size.columns == 0)
		{
			pointers.push_back({ 0 });

			_size.columns = 1;
		}
	}
	
	void Table::pushColumns(size_t amount)
	{
		for (; amount != 0; amount--)
			pushColumn();
	}
	
	void Table::pushRows(size_t amount)
	{
		for (; amount != 0; amount--)
			pushRow();
	}

	void Table::unshiftColumn()
	{
		auto& nextColumnPointers = pointers.front();

		pointers.push_front(std::vector<size_t>());

		auto& columnPointers = pointers.front();

		for (size_t row = 0; row < _size.rows; row++)
			columnPointers.push_back(nextColumnPointers[row]);

		_size.columns++;

		if (_size.rows == 0)
			_size.rows = 1;
	}

	void Table::unshiftRow()
	{
		rows.push_front(std::string());

		for (size_t column = 0; column < _size.columns; column++)
		{
			auto& columnPointers = pointers[column];

			columnPointers.insert(columnPointers.begin(), 0);
		}

		_size.rows++;

		if (_size.columns == 0)
			_size.columns = 1;
	}

	void Table::unshiftColumns(size_t amount)
	{
		for (; amount != 0; amount--)
			unshiftColumn();
	}

	void Table::unshiftRows(size_t amount)
	{
		for (; amount != 0; amount--)
			unshiftRow();
	}

	void Table::pullColumn(size_t index)
	{
		checkColumnPulling(index);

		if (index == _size.columns - 1)
			return popColumn();
		else if (index == 0)
			return shiftColumn();

		for (size_t row = 0; row < _size.rows; row++)
			set(index, row, "");

		pointers.erase(pointers.begin() + index);

		_size.columns--;

		if (_size.columns == 0)
			_size.rows = 0;
	}

	void Table::pullRow(size_t index)
	{
		checkRowPulling(index);

		if (index == _size.rows - 1)
			return popRow();
		else if (index == 0)
			return shiftRow();

		for (size_t column = 0; column < _size.columns; column++)
		{
			auto& columnPointers = pointers[column];

			columnPointers[index + 1] = columnPointers[index];

			columnPointers.erase(columnPointers.begin() + index);
		}

		rows.erase(rows.begin() + index);

		_size.rows--;

		if (_size.rows == 0)
			_size.columns = 0;
	}

	void Table::pullColumns(size_t index, size_t amount)
	{
		checkColumnPulling(index);

		if (index == _size.columns - 1)
			return popColumns(amount);
		else if (index == 0)
			return shiftColumns(amount);

		for (; amount != 0; amount--)
			if (index < _size.columns - 1)
				pullColumn(index);
			else
			{
				popColumns(amount);

				break;
			}
	}

	void Table::pullRows(size_t index, size_t amount)
	{
		checkRowPulling(index);

		if (index == _size.rows - 1)
			return popRows(amount);
		else if (index == 0)
			return shiftRows(amount);

		for (; amount != 0; amount--)
			if (index < _size.rows - 1)
				pullRow(index);
			else
			{
				popRows(amount);

				break;
			}
	}

	void Table::popColumn()
	{
		checkColumnAmount();

		auto& lastColumnPointers = pointers.back();

		for (size_t row = 0; row < _size.rows; row++)
			rows[row].erase(lastColumnPointers[row]);

		pointers.pop_back();

		_size.columns--;

		if (_size.columns == 0)
			_size.rows = 0;
	}

	void Table::popRow()
	{
		checkRowAmount();

		for (size_t column = 0; column < _size.columns; column++)
			pointers[column].pop_back();

		rows.pop_back();

		_size.rows--;

		if (_size.rows == 0)
			_size.columns = 0;
	}

	void Table::popColumns(size_t amount)
	{
		for (; amount != 0; amount--)
			popColumn();
	}

	void Table::popRows(size_t amount)
	{
		for (; amount != 0; amount--)
			popRow();
	}

	void Table::shiftColumn()
	{
		checkColumnAmount();

		for (size_t row = 0; row < _size.rows; row++)
			set(0, row, "");

		pointers.pop_front();

		_size.columns--;

		if (_size.columns == 0)
			_size.rows = 0;
	}

	void Table::shiftRow()
	{
		checkRowAmount();

		for (size_t column = 0; column < _size.columns; column++)
		{
			auto& columnPointers = pointers[column];

			columnPointers[1] = columnPointers[0];

			columnPointers.erase(columnPointers.begin());
		}

		rows.pop_front();

		_size.rows--;

		if (_size.rows == 0)
			_size.columns = 0;
	}

	void Table::shiftColumns(size_t amount)
	{
		for (; amount != 0; amount--)
			shiftColumn();
	}

	void Table::shiftRows(size_t amount)
	{
		for (; amount != 0; amount--)
			shiftRow();
	}

	void Table::checkSize(size_t column, size_t row)
	{
		if (column >= _size.columns)
			throw std::out_of_range("column index out of range");

		if (row >= _size.rows)
			throw std::out_of_range("row index out of range");
	}

	void Table::checkColumnInsertion(size_t index)
	{
		if (index > _size.columns)
			throw std::out_of_range("column index out of range");
	}

	void Table::checkRowsInsertion(size_t index)
	{
		if (index > _size.rows)
			throw std::out_of_range("row index out of range");
	}

	void Table::checkColumnPulling(size_t index)
	{
		if (index >= _size.columns)
			throw std::out_of_range("column index out of range");
	}

	void Table::checkRowPulling(size_t index)
	{
		if (index >= _size.rows)
			throw std::out_of_range("row index out of range");
	}

	void Table::checkColumnAmount()
	{
		if (_size.columns == 0)
			throw std::out_of_range("columns amount equals zero");
	}

	void Table::checkRowAmount()
	{
		if (_size.rows == 0)
			throw std::out_of_range("rows amount equals zero");
	}
}