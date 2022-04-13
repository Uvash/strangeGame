#include "stdafx.h"
#include "GameController.h"
#include "TileMap.h"
#include "Pawn.h"
#include "Game/GameMode.h"

GameController::GameController()
{

}

GameController::~GameController()
{

}

void GameController::init(EventController& newEventController)
{
	tileMap = std::make_shared<TileMap>(sf::Vector2i{ 8, 8 });
	gameMode = std::make_shared<GameMode>(*this, newEventController);
	gameMode->connectToTileMap(tileMap);
	gameMode->connectToPawns(pawnList);
	gameMode->AddPawnsAtMap();
	gameMode->addPlayers();
}

void GameController::GameStep()
{
	gameMode->tick();
}

void GameController::registredNewPawn(std::shared_ptr<Pawn> pawn)
{
	pawnList.push_back(pawn);
}

std::shared_ptr<TileMap>  GameController::getTileMap()
{
	return tileMap;
}

std::vector<std::shared_ptr<Pawn>>& GameController::getPawnList()
{
	return pawnList;
}