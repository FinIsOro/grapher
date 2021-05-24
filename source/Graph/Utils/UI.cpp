#include <Graph/Utils/UI.hpp>

namespace graph
{
	sf::Vector2f graph::scale(const sf::Vector2f& size, const sf::Vector2f& maxSize, bool out)
	{
		float k = size.y / size.x * maxSize.x > maxSize.y == out
			? maxSize.x / size.x
			: maxSize.y / size.y;

		return size * k;
	}

}

