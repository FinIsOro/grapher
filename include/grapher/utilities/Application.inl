#include "Application.hpp"

#include <functional>

namespace grapher::utilities
{
	template<class T>
	inline void Application::spawn()
	{
		static_assert(std::is_convertible<T*, Application*>::value, "Run application class must be derived from class Application");

		Application* application = (Application*)new T();

		application->run();

		delete (T*)application;
	}
}