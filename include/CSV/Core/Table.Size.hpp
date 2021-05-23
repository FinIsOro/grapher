#ifdef CSV_TABLE_NESTING

struct Size
{
	size_t columns;
	size_t rows;

	Size(size_t columns = 0, size_t rows = 0);
};

#endif