#include <CSV/Core/Table.hpp>

#include <CSV/Core/Reader.hpp>

#include <sstream>

namespace csv
{
	void Table::Builder::target(csv::Table& table)
	{
		_targer = &table;

		position.reset();
	}

	csv::Table& Table::Builder::target()
	{
		return *_targer;
	}

	void Table::Builder::append(std::string data, Append type)
	{
		if (_targer == nullptr)
			return;

		if (type == Append::Unsafely)
		{
			if (data[0] == '\n')
			{
				position.column = 0;
				position.row++;

				return;
			}

			auto targetSize = _targer->size();

			_targer->resize(
				std::max(position.column + 1, targetSize.columns),
				std::max(position.row + 1, targetSize.rows)
			);

			_targer->set(position.column, position.row, data);

			position.column++;

			return;
		}

		std::stringstream dataStream;

		dataStream << data;

		csv::Reader reader(dataStream);

		while (reader.continuable())
			append(reader.read(), Append::Unsafely);
	}
}