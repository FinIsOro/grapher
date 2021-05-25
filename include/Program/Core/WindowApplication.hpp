#pragma once

#include <SFML/Graphics.hpp>

#include <Program/Core/Application.hpp>

namespace program
{
    class WindowApplication :
        public Application
    {
    public:
        sf::RenderWindow window;

        WindowApplication();
        ~WindowApplication();

        void run() override;

    protected:
        virtual void init() = 0;
        virtual void process(const sf::Event& event);
        virtual void update(float elapsed) = 0;
        virtual void render() = 0;

    private:
        sf::Clock clock;

    };
}