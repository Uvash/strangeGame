#pragma once

#include <memory>
#include "../APlayer.h"

class EventController;
class InGameTileMap;
class HumanPlayer : public APlayer
{
public:
	HumanPlayer(GameColor newColor, EventController& newEventController , std::weak_ptr<InGameTileMap> newTileMap);
	gameMoveStatus makeMove(sf::Vector2i& startPosition, sf::Vector2i& targetPosition) override;
	~HumanPlayer() override;
private:
	EventController& eventController;
	std::weak_ptr<InGameTileMap> tileMap;
	sf::Vector2i screenCoordsToGame(sf::Vector2i screenCoords);	
	sf::Vector2i tileWithPawn;
};