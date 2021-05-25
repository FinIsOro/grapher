#include <Program/Core/WindowApplication.hpp>

#include <iostream>

using namespace sf;

namespace program
{
    WindowApplication::WindowApplication()
    {
        window.create(VideoMode(500, 500), "Application", Style::Default, ContextSettings(0, 0, 5));
    }

    WindowApplication::~WindowApplication()
        = default;

    void WindowApplication::run()
    {
        init();

        clock.restart();

        while (window.isOpen())
        {
            Event event{ };

            while (window.pollEvent(event))
                this->process(event);

            Time elapsed = clock.getElapsedTime();

            clock.restart();

            update(elapsed.asSeconds());

            window.clear();

            render();

            window.display();
        }
    }

    void WindowApplication::process(const Event& event)
    {
        switch (event.type)
        {
        case Event::Closed:
            this->window.close();

            break;
        case Event::Resized:
            this->window.setView(View({ 0, 0, (float)event.size.width, (float)event.size.height }));

            break;
        }
    }
}
