#include "stdafx.h"
#include "App.h"

App::App() : window{ sf::VideoMode(800, 600), "StrangeGame" } , eventController(window)
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
    while (eventController.needProceed())
    {
        eventController.catchEvents();

        window.clear(sf::Color::Black);
        window.display();
    }
}