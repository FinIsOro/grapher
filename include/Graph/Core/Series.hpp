#pragma once

#include <string>
#include <vector>

namespace graph
{
	class Series
	{
	public:
		#define GRAPH_SERIES_NESTING

			#include <Graph/Core/Series.Domain.hpp>
			#include <Graph/Core/Series.Range.hpp>

		#undef GRAPH_SERIES_NESTING

		const Domain& domain() const;
		std::vector<Range>& ranges();
		const std::vector<Range>& ranges() const;

		size_t length() const;
		size_t width() const;

		void push(float key, std::vector<float> values);

		void remove(float key);
		void remove(size_t index);

		void set(size_t rangeIndex, float key, float value);
		void set(size_t rangeIndex, size_t index, float value);

		void addRange();
		void addRanges(size_t amount);

		void removeRange(size_t rangeIndex);
		void removeRanges(size_t rangeIndex, size_t amount);

		void clear();

	private:
		Domain _domain;
		std::vector<Range> _ranges;

		inline void checkRangeIndex(size_t rangeIndex) const;
		inline void checkIndex(size_t index) const;
	};
}