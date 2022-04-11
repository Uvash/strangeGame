#include "stdafx.h"
#include "GameMode.h"
#include "GameController.h"
#include "InGameTileMap.h"
#include "InGamePawn.h"

GameMode::GameMode(GameController& newGameController) : gameController{ newGameController }
{

}

GameMode::~GameMode()
{
}

void GameMode::connectToTileMap(std::shared_ptr<InGameTileMap> tileMap)
{
	inGameTileMap = tileMap;
}
void GameMode::connectToPawns(std::vector<std::shared_ptr<InGamePawn>> pawnList)
{
	inGamePawns.clear();
	inGamePawns.resize(pawnList.size()); // Уж лучше один раз выдялить память руками, чем наблюдать автоматическое копирование

	for (auto pawn : pawnList)
	{
		std::weak_ptr<InGamePawn> wp = pawn; //Когда pawnList сменит тип на Pawn отнаследовав ещё и графическую часть, добавить кастование.
		inGamePawns.push_back(wp);
	}
}

bool GameMode::addPawnInGame(sf::Vector2i coordinats, GameColor color)
{
	//переделать при появлении графики
	std::shared_ptr<InGamePawn> pawnCandidat = std::make_shared<InGamePawn>(coordinats, color);
	auto map = inGameTileMap.lock();

	if (map->addPawnAtMap({pawnCandidat}, coordinats)) //если смогли успешно добавить на карту
	{
		gameController.registredNewPawn(pawnCandidat); //регистрируем окончательно
		inGamePawns.push_back({ pawnCandidat });
		return true;
	}
	
	return false;
}