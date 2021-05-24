#pragma once

#include <SFML/System.hpp>

namespace graph
{
	class ViewArea
	{
	public:
		float x;
		float y;
		float width;
		float height;

		ViewArea(float x = 0, float y = 0, float width = 0, float height = 0);

		bool include(float x, float y) const;
		bool outclude(float x, float y) const;

		ViewArea& zoom(float times, float offsetX = .5f, float offsetY = .5f);

		sf::Vector2f transform(float x, float y, float realX, float realY, float realWidth, float realHeight) const;

		bool operator==(const ViewArea& another) const;
		bool operator!=(const ViewArea& another) const;
	};
}