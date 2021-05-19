#include "Application.hpp"

namespace program
{
	template<class T>
	static void Application::run()
	{
		static_assert(std::is_convertible<T*, Application*>::value, "Run application class must be derived from class Application");

		Application* application = (Application*)new T();

		application->run();

		delete (T*)application;
	}
}