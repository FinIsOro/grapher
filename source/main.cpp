#include <Program/Console.hpp>
#include <Grapher/Grapher.hpp>

#include <iostream>

using namespace program;
using namespace grapher;

int main()
{
    Console::Show();

    Application::run<Grapher>();

    return 0;
}