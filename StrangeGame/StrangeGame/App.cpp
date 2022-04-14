#include "stdafx.h"
#include "App.h"
#include <ctime>

App::App() : window{ sf::VideoMode(800, 600), "StrangeGame" } , eventController(window), renderController(window, gameController)
{

}

App::~App()
{

}

void App::init()
{
    std::srand(std::time(nullptr)); //инициализируем генератор текущим временем
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