#pragma once
#include <SFML/Graphics.hpp>
#include "EventController.h"
#include "GameController.h"
#include "RenderController.h"

class App final
{
public:
	App();
	~App();
	void init();
	void run();
	sf::RenderWindow window;
	EventController eventController;
	GameController gameController;
	RenderController renderController;
};