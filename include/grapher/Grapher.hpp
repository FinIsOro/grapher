#pragma once

#include <Program/Application.hpp>

namespace grapher
{
	class Grapher :
		public program::Application
	{
	public:
		

	private:
		void init() override;
		void update(float elapsed) override;
		void render() override;
	};
}
