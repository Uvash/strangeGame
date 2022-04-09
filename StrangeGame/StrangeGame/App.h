#pragma once
#include <SFML/Graphics.hpp>
#include "EventController.h"

class App final
{
public:
	App();
	~App();
	void init();
	void run();
	sf::RenderWindow window;
	EventController eventController;
};