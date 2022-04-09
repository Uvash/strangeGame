#include "stdafx.h"
#include "EventController.h"


EventController::EventController(sf::Window& newWindow) : window{ newWindow }
{
}

void EventController::catchEvents()
{
    if (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            { 
                case sf::Event::Closed: {proceed = false; break; }

                case sf::Event::MouseButtonPressed :
                    {
                        if (event.mouseButton.button == sf::Mouse::Left)
                        {
                            gameEvents.lastClick = sf::Vector2i{ event.mouseButton.x, event.mouseButton.y };
                        }
                        break;
                    }

                default: break;
            }
        }
    }
}

const sf::Vector2i& EventController::getlastClick()
{
    return gameEvents.lastClick;
}
const bool& EventController::needProceed()
{
    return proceed;
}