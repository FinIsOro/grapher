#include <Grapher/Grapher.hpp>

#include <Grapher/Data.hpp>

#include <iostream>
#include <iomanip>

using namespace sf;

namespace grapher
{
	void Grapher::init()
	{
		window.setTitle("Grapher");
		window.setFramerateLimit(60);

		if (grapher::data::icon)
		{
			auto& iconInfo = ds::get("grapher::icon");

			Image icon;

			if (icon.loadFromMemory(iconInfo.begin, iconInfo.length))
			{
				auto iconSize = icon.getSize();

				window.setIcon(iconSize.x, iconSize.y, icon.getPixelsPtr());
			}
		}
	}

	void Grapher::update(float elapsed)
	{
		
	}

	void Grapher::render()
	{
		auto windowSize = window.getSize();

		VertexArray vertices;

		vertices.setPrimitiveType(LinesStrip);

		for (size_t x = 0; x < windowSize.x; ++x)
		{
			float argument = x - windowSize.x / 2.f;
			float function = (1 / (1 - argument / windowSize.x * 2.f));

			vertices.append({ Vector2f((float)(argument + windowSize.x / 2.f), (float)(windowSize.y / 2.f - function)) });
		}

		window.draw(vertices);
	}
}