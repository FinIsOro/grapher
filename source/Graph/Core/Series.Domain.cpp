#include <Graph/Core/Series.hpp>

namespace graph
{
	const std::vector<float>& Series::Domain::values()
	{
		return _values;
	}

	size_t Series::Domain::length()
	{
		return _values.size();
	}
}


