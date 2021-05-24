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
		inline const sf::Vector2f& getPosition() const;
		void setPosition(const sf::Vector2f& position);

		inline const sf::Vector2f& getSize() const;
		void setSize(const sf::Vector2f& size);

		inline const ViewArea& viewArea() const;
		inline const std::vector<Series>& series() const;
		inline size_t length() const;

		void add(const Series& series);
		void remove(size_t index);
		const Series& get(size_t index) const;

	private:
		sf::Vector2f position;
		sf::Vector2f size;

		ViewArea _viewArea = ViewArea(-5, -5, 10, 10);
		std::vector<Series> _series;

		inline void checkIndex(size_t index) const;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};
}