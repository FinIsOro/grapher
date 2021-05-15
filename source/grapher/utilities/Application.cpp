#include <utilities/Application.hpp>

namespace grapher::utilities
{
    void OnClose(Application* application)
    {
        application->window.close();
    }

    void OnResize(void* emitter, const Event::SizeEvent& event)
    {
        auto application = (Application*)emitter;

        application->window.setView(View({ 0, 0, (float)event.width, (float)event.height }));
    }

	Application::Application() :
        EventEmitter(this)
	{
		window.create(VideoMode(300, 300), "Application");

        on(Event::Closed, (Listener)OnClose);
        on(Event::Resized, (Listener)OnResize);
	}

	Application::~Application()
		= default;

	void Application::run()
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

    void Application::process(const Event& event)
    {
        switch (event.type)
        {
        case Event::Closed:
        case Event::LostFocus:
        case Event::GainedFocus:
        case Event::MouseEntered:
        case Event::MouseLeft:
            emit(event.type);

            break;
        case Event::Resized:
            emit(event.type, event.size);

            break;
        case Event::TextEntered:
            emit(event.type, event.text);

            break;
        case Event::KeyPressed:
        case Event::KeyReleased:
            emit(event.type, event.key);

            break;
        case Event::MouseWheelMoved:
            emit(event.type, event.mouseWheel);

            break;
        case Event::MouseWheelScrolled:
            emit(event.type, event.mouseWheelScroll);

            break;
        case Event::MouseButtonPressed:
        case Event::MouseButtonReleased:
            emit(event.type, event.mouseButton);

            break;
        case Event::MouseMoved:
            emit(event.type, event.mouseMove);

            break;
        case Event::JoystickButtonPressed:
        case Event::JoystickButtonReleased:
            emit(event.type, event.joystickButton);

            break;
        case Event::JoystickMoved:
            emit(event.type, event.joystickMove);

            break;
        case Event::JoystickConnected:
        case Event::JoystickDisconnected:
            emit(event.type, event.joystickConnect);

            break;
        case Event::TouchBegan:
        case Event::TouchMoved:
        case Event::TouchEnded:
            emit(event.type, event.touch);

            break;
        case Event::SensorChanged:
            emit(event.type, event.sensor);

            break;
        }
    }
}
