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

void GameController::init()
{
	tileMap = std::make_shared<InGameTileMap>(sf::Vector2i{ 8, 8 });
	gameMode = std::make_shared<GameMode>(*this);
	gameMode->connectToTileMap(tileMap);
	gameMode->connectToPawns(pawnList);
	gameMode->AddPawnsAtMap();
	bool f = gameMode->checkMove({5,5}, {5,6});
	tileMap->printMap();
}

void GameController::GameStep()
{

}

void GameController::registredNewPawn(std::shared_ptr<InGamePawn> pawn)
{
	pawnList.push_back(pawn);
}