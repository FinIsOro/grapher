#pragma once

namespace csv
{
	struct Range
	{
		size_t start;
		size_t end;

		Range(size_t start = 0, size_t end = 0);

		bool include(size_t value) const;
		bool outclude(size_t value) const;

		size_t size() const;
	};
}