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

		struct Size
		{
			size_t columns;
			size_t rows;

			Size(size_t columns = 0, size_t rows = 0);
		};

		struct Bound
		{
			struct Range
			{
				size_t start;
				size_t end;

				Range(size_t start = 0, size_t end = 0);

				inline bool include(size_t value) const;
				inline bool outclude(size_t value) const;

				inline size_t size() const;
			};

			Range column;
			Range row;

			Bound(Range column = Range(), Range row = Range());

			bool include(size_t column, size_t row) const;
			bool outclude(size_t column, size_t row) const;

			Size size() const;
		};

		struct CellInfo abstract
		{
		public:
			enum class Type
			{
				Number,
				String,
			};

			void* data() const;

			virtual Type type() const abstract;
			virtual size_t size() const abstract;

		protected:
			Table* parent = nullptr;
			size_t position = 0;
		};

		struct NumberCellInfo :
			Table::CellInfo
		{
			Type type() const override;
			size_t size() const override;

		private:
			NumberCellInfo(Table* parent, size_t position);

			friend Builder;
		};

		struct StringCellInfo :
			Table::CellInfo
		{
			Type type() const override;
			size_t size() const override;

		private:
			size_t length;

			StringCellInfo(Table* parent, size_t position, size_t length);

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

			Table& build() const;

		private:
			size_t row;
			size_t column;

			Table* table = new Table();
		};

		CellInfo* at(size_t column, size_t row) const;

		Size volume() const;

	private:
		std::map<size_t, std::map<size_t, CellInfo*>> cells;
		std::deque<NumberCellInfo> numberCells;
		std::deque<StringCellInfo> stringCells;

		std::string data;
		Size size;

		Table();

		friend CellInfo;
		friend Builder;
	};
}