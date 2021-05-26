#include <Grapher/Core/Application.hpp>

#include <Grapher/Data.hpp>

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace sf;
using namespace graph;
using namespace std;

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
	}

	void Application::process(const sf::Event& event)
	{
		program::WindowApplication::process(event);

		switch (event.type)
		{
		case Event::MouseWheelScrolled: {
			if (chartHolding)
				break;
				
			ViewArea& chartViewArea = chart.viewArea();
			Vector2f chartSize = chart.getSize();

			Vector2f viewAreaSize = graph::scale({ 1, 1 }, { chartSize.x, chartSize.y });
			Vector2f viewAreaPosition = (chartSize - viewAreaSize) / 2.f;

			Vector2f offset = Vector2f(event.mouseWheelScroll.x, event.mouseWheelScroll.y) - viewAreaPosition;

			offset.x /= viewAreaSize.x;
			offset.y /= viewAreaSize.y;

			offset -= Vector2f(.5f, .5f);

			chartViewArea.zoom(pow(1.5, event.mouseWheelScroll.delta), offset.x, -offset.y);

			break;
		}
		case Event::MouseButtonPressed: {
			if (!chartHolding && event.mouseButton.button == Mouse::Left)
			{
				chartHolding = true;

				ViewArea& chartViewArea = chart.viewArea();
				Vector2f chartSize = chart.getSize();

				Vector2f viewAreaSize = graph::scale({ 1, 1 }, { chartSize.x, chartSize.y });
				Vector2f viewAreaPosition = (chartSize - viewAreaSize) / 2.f;

				startHoldingPosition = Vector2f(event.mouseButton.x, event.mouseButton.y) - viewAreaPosition;

				startHoldingPosition.x /= viewAreaSize.x;
				startHoldingPosition.y /= -viewAreaSize.y;

				chartHoldingVeiwArea = chartViewArea;
			}

			break;
		}
		case Event::MouseButtonReleased: {
			if (chartHolding && event.mouseButton.button == Mouse::Left)
				chartHolding = false;

			break;
		}
		}
	}

	void Application::update(float elapsed)
	{
		chart.setSize((Vector2f)window.getSize());

		chart.update();

		if (chartHolding)
		{
			ViewArea& chartViewArea = chart.viewArea();
			Vector2f chartSize = chart.getSize();

			Vector2f viewAreaSize = graph::scale({ 1, 1 }, { chartSize.x, chartSize.y });
			Vector2f viewAreaPosition = (chartSize - viewAreaSize) / 2.f;

			Vector2i mousePosition = Mouse::getPosition(this->window);

			Vector2f currentHoldingPosition = Vector2f(mousePosition.x, mousePosition.y) - viewAreaPosition;

			currentHoldingPosition.x /= viewAreaSize.x;
			currentHoldingPosition.y /= -viewAreaSize.y;

			chartViewArea.x = chartHoldingVeiwArea.x + (startHoldingPosition.x - currentHoldingPosition.x) * chartViewArea.width;
			chartViewArea.y = chartHoldingVeiwArea.y + (startHoldingPosition.y - currentHoldingPosition.y) * chartViewArea.height;
		}
	}

	void Application::render()
	{
		window.draw(chart);
	}
}