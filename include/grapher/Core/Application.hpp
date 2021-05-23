#pragma once

#include <Program/Core.hpp>

namespace grapher
{
	class Application :
		public program::WindowApplication
	{
	public:
		

	private:
		void init() override;
		void update(float elapsed) override;
		void render() override;
	};
}
