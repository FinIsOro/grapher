#include <Graph/Core/Series.hpp>

namespace graph
{
	const std::vector<float>& Series::Range::values()
	{
		return _values;
	}

	size_t Series::Range::length()
	{
		return _values.size();
	}
}