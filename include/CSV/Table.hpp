#pragma once

#include <string>
#include <deque>
#include <map>

namespace csv
{
	class Table
	{
	public:
		class Builder;

		struct CellInfo abstract
		{
		public:
			enum class Type
			{
				Number,
				String,
			};

			void* data();

			virtual Type type() abstract;
			virtual unsigned int size() abstract;

		protected:
			Table* parent;
			size_t position = 0;
		};

		struct NumberCellInfo :
			Table::CellInfo
		{
			Type type() override;
			unsigned int size() override;

		private:
			NumberCellInfo(Table* parent, size_t position);

			friend Builder;
		};

		struct StringCellInfo :
			Table::CellInfo
		{
			Type type() override;
			unsigned int size() override;

		private:
			unsigned int length;

			StringCellInfo(Table* parent, size_t position, unsigned int length);

			friend Builder;
		};

		class Builder
		{
		public:
			~Builder();

			void reset();

			void append(float value);
			void append(std::string value);
			
			void line();

			Table& build();

		private:
			unsigned int row;
			unsigned int column;

			Table* table = new Table();
		};

		CellInfo* at(unsigned int column, unsigned int row);

	private:
		std::map<unsigned int, std::map<unsigned int, CellInfo*>> cells;
		std::deque<NumberCellInfo> numberCells;
		std::deque<StringCellInfo> stringCells;

		std::string data;

		Table() = default;

		friend CellInfo;
		friend Builder;
	};
}