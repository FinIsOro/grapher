#pragma once

#include <Graph/Core/Series.hpp>
#include <Graph/Graphics/ViewArea.hpp>

#include <SFML/Graphics.hpp>

namespace graph
{
	class Chart :
		public sf::Drawable
	{
	public:
		Chart();
		
		const sf::Vector2f& getPosition() const;
		void setPosition(const sf::Vector2f& position);

		const sf::Vector2f& getSize() const;
		void setSize(const sf::Vector2f& size);

		ViewArea& viewArea();
		const std::vector<Series>& series() const;
		size_t length() const;

		void add(const Series& series);
		void remove(size_t index);
		const Series& get(size_t index) const;

		void defaultView();

		void update();

	private:
		sf::Vector2f position;
		sf::Vector2f size;
		std::vector<sf::Color> colors;

		sf::Font font;
		
		ViewArea _viewArea = ViewArea(-50, -50, 100, 100);
		std::vector<Series> _series;

		inline void checkIndex(size_t index) const;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};
}