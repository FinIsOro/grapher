#include <Graph/Graphics/Chart.hpp>
#include <Graph/Utils/UI.hpp>

using namespace sf;

namespace graph
{
	const Vector2f& Chart::getPosition() const
	{
		return position;
	}

	void Chart::setPosition(const Vector2f& position)
	{
		this->position = position;
	}

	const Vector2f& Chart::getSize() const
	{
		return size;
	}

	void Chart::setSize(const Vector2f& size)
	{
		this->size = size;
	}

	const ViewArea& Chart::viewArea() const
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
		Vector2f viewAreaSize = graph::scale({ 1, 1 }, { size.x, size.y });
		Vector2f viewAreaPosition = Vector2f(size.x - viewAreaSize.x, (size.y - viewAreaSize.y) / 2);

		sf::RectangleShape mask;

		mask.setSize(viewAreaSize);
		mask.setPosition(viewAreaPosition);

		for (auto& series : _series)
		{
			auto& domainValues = series.domain().values();
			auto& ranges = series.ranges();

			size_t length = series.length();

			for (auto& range : ranges)
			{
				VertexArray vertices(LinesStrip);

				auto& rangeValues = range.values();

				for (size_t index = 0; index < length; index++)
					vertices.append({
						_viewArea.transform(
							domainValues[index], rangeValues[index],
							viewAreaPosition.x, viewAreaPosition.y,
							viewAreaSize.x, viewAreaSize.y
						)
					});

				target.draw(vertices);
			}
		}
	}
}