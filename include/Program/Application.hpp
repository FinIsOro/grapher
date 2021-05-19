#pragma once

#include <SFML/Graphics.hpp>

#include <Program/EventEmitter.hpp>

namespace program
{
	class Application :
        protected EventEmitter<sf::Event::EventType>
	{
    public:
        template<class T>
        static void run();

        sf::RenderWindow window;

        Application();
        ~Application();

        void run();

    protected:
        virtual void init() = 0;
        virtual void update(float elapsed) = 0;
        virtual void render() = 0;

    private:
        sf::Clock clock;

        void process(const sf::Event& event);
	};
}

#include "Application.inl"