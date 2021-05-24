#ifdef GRAPH_SERIES_NESTING

class Domain
{
	friend graph::Series;

public:
	const std::vector<float>& values() const;
	size_t length() const;

private:
	std::vector<float> _values;
};

#endif