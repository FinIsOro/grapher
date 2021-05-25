#pragma once

#include <Program/Core.hpp>
#include <Graph/Graphics.hpp>

namespace grapher
{
	class Application :
		public program::WindowApplication
	{
	public:
		graph::Chart chart;
		

	private:
		bool chartHolding = false;
		sf::Vector2f startHoldingPosition;
		graph::ViewArea chartHoldingVeiwArea;

		void init() override;
		void process(const sf::Event& event) override;
		void update(float elapsed) override;
		void render() override;
	};
}
