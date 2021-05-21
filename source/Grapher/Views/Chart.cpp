#include <Grapher/Views/Chart.hpp>

namespace grapher::views
{
	Chart::ViewArea Chart::view()
	{
		return viewArea;
	}

	void Chart::view(ViewArea viewArea)
	{
		if (this->viewArea == viewArea)
			return;

		this->viewArea = viewArea;

		recalculate();
	}

	void Chart::add(const Series& series)
	{
		this->seriesData.push_back(series);

		recalculate();
	}

	void Chart::recalculate()
	{

	}

	void Chart::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{

	}

	Chart::ViewArea::ViewArea(float x, float y, float width, float height) :
		x(x), y(y), width(width), height(height)
	{ }

	bool Chart::ViewArea::include(float x, float y)
	{
		return	x >= this->x && x <= this->x + this->width &&
				y >= this->y && y <= this->y + this->height;
	}

	bool Chart::ViewArea::outclude(float x, float y)
	{
		return	x < this->x || x > this->x + this->width ||
				y < this->y || y > this->y + this->height;
	}

	Chart::ViewArea Chart::ViewArea::zoom(float times, float offsetX, float offsetY)
	{
		float zoomedWidth = width / times;
		float zoomedHeight = height / times;

		return ViewArea(x + (width - zoomedWidth) * offsetX, y + (height - zoomedHeight) * offsetY, zoomedWidth, zoomedHeight);
	}

	bool Chart::ViewArea::operator==(const ViewArea& another)
	{
		return x == another.x && y == another.y && width == another.width && height == another.height;
	}

	bool Chart::ViewArea::operator!=(const ViewArea& another)
	{
		return x != another.x || y != another.y || width != another.width || height != another.height;
	}
}