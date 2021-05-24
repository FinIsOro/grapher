#pragma once

#include <Program/Core.hpp>
#include <Graph/Graphics/Chart.hpp>

namespace grapher
{
	class Application :
		public program::WindowApplication
	{
	public:
		

	private:
		graph::Chart chart;

		void init() override;
		void update(float elapsed) override;
		void render() override;
	};
}
