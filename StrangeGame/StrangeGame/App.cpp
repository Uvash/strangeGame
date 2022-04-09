#include "stdafx.h"
#include "App.h"

App::App() : window{ sf::VideoMode(800, 600), "StrangeGame" }
{

}

App::~App()
{

}

void App::init()
{

}

void App::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Black);
        window.display();
    }
}