#include <Grapher/Core.hpp>

#include <iostream>

int main()
{
    program::Console::Hide();

    program::Application* application = new grapher::Application();

    application->run();

    delete application;

    return 0;
}