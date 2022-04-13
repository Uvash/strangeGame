#include <stdafx.h>
#include <iostream>
#include "HumanPlayer.h"
#include "EventController.h"
#include "../InGameTileMap.h"

HumanPlayer::HumanPlayer(GameColor newColor, EventController& newEventController, std::weak_ptr<InGameTileMap> newTileMap) \
	: APlayer{ newColor }, eventController{ newEventController }, tileMap{ newTileMap }, tileWithPawn{-1, -1}
{

}

gameMoveStatus HumanPlayer::makeMove(sf::Vector2i& startPosition, sf::Vector2i& targetPosition)
{
	sf::Vector2i lastClick = eventController.getlastClick();
	if (lastClick.x == 0 && lastClick.y == 0)	//Если мы ни куда не кликаем, то ни чего не делаем
	{
		return gameMoveStatus::dontMove;
	}

	sf::Vector2i clickInGameCoords = screenCoordsToGame(lastClick);
	auto pMap = tileMap.lock();

	if (!pMap->inRange(clickInGameCoords))
	{
		return gameMoveStatus::dontMove;
	}

	if (tileWithPawn != sf::Vector2i{ -1, -1 })
	{
		startPosition = tileWithPawn;
		targetPosition = clickInGameCoords;

		tileWithPawn = sf::Vector2i{ -1, -1 };
		return gameMoveStatus::move;
	}

	tileWithPawn = clickInGameCoords;

	return gameMoveStatus::dontMove;
}

HumanPlayer::~HumanPlayer()
{

}

sf::Vector2i HumanPlayer::screenCoordsToGame(sf::Vector2i screenCoords)
{
	//Если честно вся функция один большой костыль
	auto pMap = tileMap.lock();
	sf::Vector2i mapSize = pMap->getSize();
	sf::Vector2i tileSizeInScreen = { 800 / mapSize.x , 600 / mapSize.y };
	sf::Vector2i gameCoords = { screenCoords.x / tileSizeInScreen.x, screenCoords.y / tileSizeInScreen.y };
	return gameCoords;
}