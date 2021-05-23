#ifdef GRAPH_SERIES_NESTING

class Domain
{
	friend graph::Series;

public:
	const std::vector<float>& values();
	size_t length();

private:
	std::vector<float> _values;
};

#endif