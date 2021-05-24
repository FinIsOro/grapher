#ifdef CSV_TABLE_NESTING

struct Area
{
public:
	csv::Range column;
	csv::Range row;

	Area(csv::Range column = csv::Range(), csv::Range row = csv::Range());

	bool include(size_t column, size_t row) const;
	bool outclude(size_t column, size_t row) const;

	csv::Table::Size size() const;
};

#endif