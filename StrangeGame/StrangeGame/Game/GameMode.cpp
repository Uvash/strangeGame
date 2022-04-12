#include "stdafx.h"
#include <math.h>
#include "GameMode.h"
#include "GameController.h"
#include "InGameTileMap.h"
#include "InGamePawn.h"
#include "Tile.h"
#include "Players/HumanPlayer.h"

GameMode::GameMode(GameController& newGameController, EventController& NewEventController) :	gameController{ newGameController }, eventController{ NewEventController } {}

GameMode::~GameMode() {}

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

bool GameMode::checkMove(sf::Vector2i start, sf::Vector2i target)
{
	if (start == target)	//Под себя ходить мы не должны.
		return false;

	auto map = inGameTileMap.lock();

	if (!map->inRange(start)) // Проверим на попытку сбежать с поля
		return false;
	if (!map->inRange(target))
		return false;

	const Tile& targetTile = map->getTile(target); 
	const Tile& positionTile = map->getTile(start);

	if (positionTile.isFree()) //С пустой клетки точно ни чего ходить не может
		return false;

	if (!targetTile.isFree()) //Нельзя ходить на тайл, если там уже кто-то есть
		return false;
	
	if (std::abs(target.x - start.x) + std::abs(target.y - start.y) <= 1) // Вычисляем дистанцию в кол-ве ходов до цели
		return true;

	return false;
}

bool GameMode::movePawn(sf::Vector2i start, sf::Vector2i target)
{
	if (!checkMove(start, target))
		return false;

	auto map = inGameTileMap.lock();
	map->swapPawns(start, target);
}

void GameMode::addPlayers()
{
	auto humPlayer = std::make_shared<HumanPlayer>(GameColor::white, eventController, inGameTileMap);
	players.push_back(std::static_pointer_cast<APlayer>(humPlayer));
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

void GameMode::tick()
{
	sf::Vector2i start;
	sf::Vector2i finish;
	if (players[0]->makeMove(start, finish) == gameMoveStatus::move)
	{
		movePawn(start, finish);
	}
}