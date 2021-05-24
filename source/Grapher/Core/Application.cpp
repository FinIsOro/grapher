#include <Grapher/Core/Application.hpp>

#include <Grapher/Data.hpp>

#include <iostream>
#include <iomanip>

using namespace sf;

namespace grapher
{
	void Application::init()
	{
		window.setTitle("Grapher");
		window.setFramerateLimit(60);

		if (grapher::data::icon)
		{
			auto& iconInfo = ds::get("grapher::icon");

			Image icon;

			if (icon.loadFromMemory(iconInfo.data, iconInfo.length))
			{
				auto iconSize = icon.getSize();

				window.setIcon(iconSize.x, iconSize.y, icon.getPixelsPtr());
			}
		}

		graph::Series series;

		series.addRange();

		series.push(-3, { -3 });
		series.push(-2, { 3 });
		series.push(-1, { 4 });
		series.push(0, { 0 });
		series.push(1, { 5 });

		chart.add(series);
	}

	void Application::update(float elapsed)
	{
		chart.setSize((Vector2f)window.getSize());
	}

	void Application::render()
	{
		window.draw(chart);
	}
}