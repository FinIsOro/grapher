#pragma once

#include <utilities/Application.hpp>

using namespace grapher::utilities;

namespace grapher::core
{
	class Grapher :
		public Application
	{


	private:
		void init() override;
		void update(float elapsed) override;
		void render() override;
	};
}
