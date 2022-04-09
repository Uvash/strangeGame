#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class App final
{
public:
	App();
	~App();
	void init();
	void run();
	sf::RenderWindow window;

};