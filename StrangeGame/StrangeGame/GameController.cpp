#include "stdafx.h"
#include "GameController.h"
#include "Game/InGameTileMap.h"
#include "Game/InGamePawn.h"
#include "Game/GameMode.h"

GameController::GameController()
{

}

GameController::~GameController()
{

}

void GameController::init(EventController& newEventController)
{
	tileMap = std::make_shared<InGameTileMap>(sf::Vector2i{ 8, 8 });
	gameMode = std::make_shared<GameMode>(*this, newEventController);
	gameMode->connectToTileMap(tileMap);
	gameMode->connectToPawns(pawnList);
	gameMode->AddPawnsAtMap();
	gameMode->addPlayers();
	tileMap->printMap();
	gameMode->movePawn({ 5, 5 }, { 5, 4 });
	tileMap->printMap();
}

void GameController::GameStep()
{
	gameMode->tick();
}

void GameController::registredNewPawn(std::shared_ptr<InGamePawn> pawn)
{
	pawnList.push_back(pawn);
}