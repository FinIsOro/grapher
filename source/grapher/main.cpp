#include <utilities/Application.hpp>
#include <utilities/Console.hpp>
#include <core/Grapher.hpp>
#include <iostream>

using namespace grapher::utilities;

using MainApplication = grapher::core::Grapher;

int main()
{
    Console::Hide();

    Application::spawn<MainApplication>();

    return 0;
}