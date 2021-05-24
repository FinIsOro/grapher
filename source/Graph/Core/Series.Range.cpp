#include <Graph/Core/Series.hpp>

namespace graph
{
	const std::vector<float>& Series::Range::values() const
	{
		return _values;
	}

	size_t Series::Range::length() const
	{
		return _values.size();
	}
}
