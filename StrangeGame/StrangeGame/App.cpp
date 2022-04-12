#include "stdafx.h"
#include "App.h"

App::App() : window{ sf::VideoMode(800, 600), "StrangeGame" } , eventController(window), renderController(window)
{

}

App::~App()
{

}

void App::init()
{
    gameController.init(eventController);
    renderController.init();
}

void App::run()
{
    while (eventController.needProceed())
    {
        eventController.catchEvents();
        gameController.GameStep();
        renderController.updateScreen();

    }
}