#include <utilities/Console.hpp>

#include <Windows.h>

namespace grapher::utilities
{
	void Console::Hide()
	{
		ShowWindow(GetConsoleWindow(), SW_HIDE);
	}

	void Console::Show()
	{
		ShowWindow(GetConsoleWindow(), SW_SHOW);
	}

	bool Console::IsVisible()
	{
		return IsWindowVisible(GetConsoleWindow()) != FALSE;
	}
}