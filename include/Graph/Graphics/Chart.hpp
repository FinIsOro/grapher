#pragma once

#include <Graph/Core/Series.hpp>

#include <SFML/Graphics.hpp>

namespace graph
{
	class Chart :
		sf::Drawable
	{
	public:
		#define GRAPH_CHART_NESTING
			
			#include <Graph/Graphics/Chart.ViewArea.hpp>

		#undef GRAPH_CHART_NESTING

		inline const ViewArea& viewArea() const;
		inline const std::vector<Series>& series() const;

		inline size_t length() const;

		void add(const Series& series);
		void remove(size_t index);
		const Series& get(size_t index) const;

	private:
		ViewArea _viewArea;

		std::vector<Series> _series;

		inline void checkIndex(size_t index) const;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};
}