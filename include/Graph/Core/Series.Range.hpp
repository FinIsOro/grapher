#ifdef GRAPH_SERIES_NESTING

class Range
{
	friend graph::Series;

public:
	std::string name;

	const std::vector<float>& values();
	size_t length();

private:
	std::vector<float> _values;
};

#endif