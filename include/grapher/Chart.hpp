#pragma once

#include <SFML/Graphics.hpp>

namespace grapher
{
	class Chart :
		sf::Drawable
	{


	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}