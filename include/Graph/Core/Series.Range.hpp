#ifdef GRAPH_SERIES_NESTING

class Range
{
	friend graph::Series;

public:
	std::string name;

	const std::vector<float>& values() const;
	size_t length() const;

private:
	std::vector<float> _values;

	Range() = default;
};

#endif