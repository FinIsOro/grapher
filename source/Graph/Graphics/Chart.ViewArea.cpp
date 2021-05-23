#include <Graph/Graphics/Chart.hpp>

using namespace sf;

namespace graph
{
	Chart::ViewArea::ViewArea(float x, float y, float width, float height) :
		x(x), y(y), width(width), height(height)
	{ }

	bool Chart::ViewArea::include(float x, float y) const
	{
		return	x >= this->x && x <= this->x + this->width &&
			y >= this->y && y <= this->y + this->height;
	}

	bool Chart::ViewArea::outclude(float x, float y) const
	{
		return	x < this->x || x > this->x + this->width ||
			y < this->y || y > this->y + this->height;
	}

	Chart::ViewArea& Chart::ViewArea::zoom(float times, float offsetX, float offsetY)
	{
		float zoomedWidth = width / times;
		float zoomedHeight = height / times;

		x = x + (width - zoomedWidth) * offsetX;
		y = y + (height - zoomedHeight) * offsetY;

		width = zoomedWidth;
		height = zoomedHeight;

		return *this;
	}

	Vector2f Chart::ViewArea::transform(float x, float y, float realWidth, float realHeight) const
	{
		return sf::Vector2f((x - this->x) / this->width * realWidth, (y - this->y) / this->height * realHeight);
	}

	bool Chart::ViewArea::operator==(const ViewArea& another) const
	{
		return x == another.x && y == another.y && width == another.width && height == another.height;
	}

	bool Chart::ViewArea::operator!=(const ViewArea& another) const
	{
		return x != another.x || y != another.y || width != another.width || height != another.height;
	}
}