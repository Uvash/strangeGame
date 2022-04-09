#pragma once
/*
	����� EventController - ������ ������� ���������� � ����, � �������������� ��
*/
#include <SFML/Graphics.hpp>

struct GameEvents
{
	sf::Vector2i lastClick;
};

class EventController final
{
public:
	EventController() = delete; // ���� � ��� �� ����� ����, �� ������ �� ����� ������?
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