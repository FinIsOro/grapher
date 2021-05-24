#include <Graph/Graphics/ViewArea.hpp>

using namespace sf;

namespace graph
{
	ViewArea::ViewArea(float x, float y, float width, float height) :
		x(x), y(y), width(width), height(height)
	{ }

	bool ViewArea::include(float x, float y) const
	{
		return	x >= this->x && x <= this->x + this->width &&
			y >= this->y && y <= this->y + this->height;
	}

	bool ViewArea::outclude(float x, float y) const
	{
		return	x < this->x || x > this->x + this->width ||
			y < this->y || y > this->y + this->height;
	}

	ViewArea& ViewArea::zoom(float times, float offsetX, float offsetY)
	{
		float zoomedWidth = width / times;
		float zoomedHeight = height / times;

		x = x + (width - zoomedWidth) * offsetX;
		y = y + (height - zoomedHeight) * offsetY;

		width = zoomedWidth;
		height = zoomedHeight;

		return *this;
	}

	Vector2f ViewArea::transform(float x, float y, float realX, float realY, float realWidth, float realHeight) const
	{
		return sf::Vector2f(realX + (x - this->x) / this->width * realWidth, realY + realHeight * (1 - (y - this->y) / this->height));
	}

	bool ViewArea::operator==(const ViewArea& another) const
	{
		return x == another.x && y == another.y && width == another.width && height == another.height;
	}

	bool ViewArea::operator!=(const ViewArea& another) const
	{
		return x != another.x || y != another.y || width != another.width || height != another.height;
	}
}