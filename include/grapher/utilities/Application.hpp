#pragma once

#include <SFML/Graphics.hpp>

#include <utilities/EventEmitter.hpp>

using namespace sf;

namespace grapher::utilities
{
	class Application :
        protected EventEmitter<Event::EventType>
	{
	public:
		template<class T>
		static void spawn();

        RenderWindow window;

        Application();
        ~Application();

        void run();

    protected:
        virtual void init() = 0;
        virtual void update(float elapsed) = 0;
        virtual void render() = 0;

    private:
        Clock clock;

        void process(const sf::Event& event);
	};
}

#include "Application.inl"
