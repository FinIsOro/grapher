#include <core/Grapher.hpp>
#include <data/icon.hpp>

#include <iostream>
#include <iomanip>

namespace grapher::core
{
	void Grapher::init()
	{
		window.setTitle("Grapher");
		window.setFramerateLimit(60);
		
		Image icon;

		if (icon.loadFromMemory(iconData, 27661))
			window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	}

	void Grapher::update(float elapsed)
	{

	}

	void Grapher::render()
	{

	}
}