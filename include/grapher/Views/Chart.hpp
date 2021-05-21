#pragma once

#include <Grapher/Series.hpp>

#include <SFML/Graphics.hpp>

namespace grapher::views
{
	class Chart :
		sf::Drawable
	{
		struct ViewArea
		{
			float x;
			float y;
			float width;
			float height;

			ViewArea(float x = 0, float y = 0, float width = 0, float height = 0);

			bool include(float x, float y);
			bool outclude(float x, float y);

			ViewArea zoom(float times, float offsetX = .5f, float offsetY = .5f);

			bool operator==(const ViewArea& another);
			bool operator!=(const ViewArea& another);
		};

		ViewArea view();
		void view(ViewArea viewArea);

		void add(const Series& series);

	private:
		ViewArea viewArea = ViewArea(-5, -5, 10, 10);

		void recalculate();

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		std::vector<Series> seriesData;
		std::vector<Series> seriesView;
	};
} 