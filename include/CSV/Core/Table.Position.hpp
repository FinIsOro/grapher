#ifdef CSV_TABLE_NESTING

struct Position
{
	size_t column;
	size_t row;

	Position(size_t column = 0, size_t row = 0);

	void reset();
	void set(size_t column, size_t row);
};

#endif