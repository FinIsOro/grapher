#pragma once

#include <SFML/Graphics.hpp>

#include <Program/Core/Application.hpp>
#include <Program/Utils/EventEmitter.hpp>

namespace program
{
    class WindowApplication :
        public Application,
        protected EventEmitter<sf::Event::EventType>
    {
    public:
        sf::RenderWindow window;

        WindowApplication();
        ~WindowApplication();

        void run() override;

    protected:
        virtual void init() = 0;
        virtual void update(float elapsed) = 0;
        virtual void render() = 0;

    private:
        sf::Clock clock;

        void process(const sf::Event& event);
    };
}