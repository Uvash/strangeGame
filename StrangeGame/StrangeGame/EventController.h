#pragma once
/*
	класс EventController - дёргает события приходящие в окно, и перенаправляет их
*/
#include <SFML/Graphics.hpp>

struct GameEvents
{
	sf::Vector2i lastClick;
};

class EventController final
{
public:
	EventController() = delete; // Если у нас не будет окна, то откуда мы брать ивенты?
	EventController(sf::Window &newWindow);
	~EventController() = default;

	void catchEvents();

	const sf::Vector2i & getlastClick();
	const bool & needProceed();
private:
	sf::Window& window;
	GameEvents gameEvents;
	bool proceed = true;
};