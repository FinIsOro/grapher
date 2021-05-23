#include <Graph/Graphics/Chart.hpp>

using namespace sf;

namespace graph
{
	const Chart::ViewArea& Chart::viewArea() const
	{
		return _viewArea;
	}

	const std::vector<Series>& Chart::series() const
	{
		return _series;
	}

	void Chart::add(const Series& series)
	{
		_series.push_back(series);
	}

	void Chart::remove(size_t index)
	{
		checkIndex(index);

		_series.erase(_series.begin() + index);
	}

	const Series& Chart::get(size_t index) const
	{
		checkIndex(index);

		return _series[index];
	}

	size_t Chart::length() const
	{
		return _series.size();
	}

	void Chart::checkIndex(size_t index) const
	{
		if (index >= length())
			throw std::out_of_range("index out of range");
	}

	void Chart::draw(RenderTarget& target, RenderStates states) const
	{
	}
}