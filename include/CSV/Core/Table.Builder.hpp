#ifdef CSV_TABLE_NESTING

class Builder
{
public:
	enum class Append
	{
		Safely,
		Unsafely,
	};

	csv::Table::Position position;

	Builder(csv::Table& table);
	Builder() = default;

	void target(csv::Table& table);
	csv::Table& target();

	void append(std::string data = "\n", Append type = Append::Safely);

private:
	csv::Table* _target = nullptr;
};

#endif