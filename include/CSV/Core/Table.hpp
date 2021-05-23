#pragma once

#include <string>
#include <vector>
#include <deque>

namespace csv
{
	class Table
	{
	public:
		#define CSV_TABLE_NESTING

			#include <CSV/Core/Table.Position.hpp>
			#include <CSV/Core/Table.Size.hpp>
			#include <CSV/Core/Table.Builder.hpp>

		#undef CSV_TABLE_NESTING

		Size size();

		std::string get(size_t column, size_t row);
		void set(size_t column, size_t row, std::string value);

		void resize(size_t columns, size_t rows);

		void insertColumn(size_t index);
		void insertRow(size_t index);

		void insertColumns(size_t index, size_t amount);
		void insertRows(size_t index, size_t amount);

		void pushColumn();
		void pushRow();

		void pushColumns(size_t amount);
		void pushRows(size_t amount);

		void unshiftColumn();
		void unshiftRow();

		void unshiftColumns(size_t amount);
		void unshiftRows(size_t amount);

		void pullColumn(size_t index);
		void pullRow(size_t index);

		void pullColumns(size_t index, size_t amount);
		void pullRows(size_t index, size_t amount);

		void popColumn();
		void popRow();

		void popColumns(size_t amount);
		void popRows(size_t amount);

		void shiftColumn();
		void shiftRow();

		void shiftColumns(size_t amount);
		void shiftRows(size_t amount);

	private:
		Size _size;

		std::deque<std::vector<size_t>> pointers;
		std::deque<std::string> rows;

		inline void checkSize(size_t column, size_t row);
		inline void checkColumnInsertion(size_t index);
		inline void checkRowsInsertion(size_t index);
		inline void checkColumnPulling(size_t index);
		inline void checkRowPulling(size_t index);
		inline void checkColumnAmount();
		inline void checkRowAmount();
	};
}