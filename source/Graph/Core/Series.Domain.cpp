#include <Graph/Core/Series.hpp>

namespace graph
{
	const std::vector<float>& Series::Domain::values() const
	{
		return _values;
	}

	size_t Series::Domain::length() const
	{
		return _values.size();
	}
}