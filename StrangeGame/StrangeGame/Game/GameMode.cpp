#include "stdafx.h"
#include <math.h>
#include "GameMode.h"
#include "GameController.h"
#include "InGameTileMap.h"
#include "InGamePawn.h"
#include "Tile.h"

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

bool GameMode::checkMove(sf::Vector2i position, sf::Vector2i target)
{
	auto map = inGameTileMap.lock();
	const Tile& targetTile = map->getTile(target); 

	if (!targetTile.isFree()) //Нельзя ходить на тайл, если там уже кто-то есть
		return false;

	if(position == target)	//И под себя то же не стоит
		return false;
	
	if (std::abs(target.x - position.x) + std::abs(target.y - position.y) <= 1) // Вычисляем дистанцию в кол-ве ходов до цели
		return true;

	return false;
}


void GameMode::AddPawnsAtMap() 
{
	//Не самое правильное решение, но если прижмёт напишем класс отвечающий за спавн...
	addPawnInGame({ 0, 0 }, GameColor::white); addPawnInGame({ 1, 0 }, GameColor::white); addPawnInGame({ 2, 0 }, GameColor::white);
	addPawnInGame({ 0, 1 }, GameColor::white); addPawnInGame({ 1, 1 }, GameColor::white); addPawnInGame({ 2, 1 }, GameColor::white);
	addPawnInGame({ 0, 2 }, GameColor::white); addPawnInGame({ 1, 2 }, GameColor::white); addPawnInGame({ 2, 2 }, GameColor::white);

	addPawnInGame({ 5, 5 }, GameColor::black); addPawnInGame({ 6, 5 }, GameColor::black); addPawnInGame({ 7, 5 }, GameColor::black);
	addPawnInGame({ 5, 6 }, GameColor::black); addPawnInGame({ 6, 6 }, GameColor::black); addPawnInGame({ 7, 6 }, GameColor::black);
	addPawnInGame({ 5, 7 }, GameColor::black); addPawnInGame({ 6, 7 }, GameColor::black); addPawnInGame({ 7, 7 }, GameColor::black);
}