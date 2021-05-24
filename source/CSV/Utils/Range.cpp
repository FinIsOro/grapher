#include <CSV/Utils/Range.hpp>

namespace csv
{
	Range::Range(size_t start, size_t end) :
		start(start), end(end)
	{ }

	bool Range::include(size_t value) const
	{
		return value >= start && value <= end;
	}

	bool Range::outclude(size_t value) const
	{
		return value < start || value > end;
	}

	size_t Range::size() const
	{
		return end - start;
	}
}