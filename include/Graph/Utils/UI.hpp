#pragma once

#include <SFML/Graphics.hpp>

namespace graph
{
	sf::Vector2f scale(const sf::Vector2f& size, const sf::Vector2f& maxSize, bool out = false);
}