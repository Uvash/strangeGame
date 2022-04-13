#pragma once
/*
	класс GameController - управл€ет пам€тью игровых объЄктов (режимом игры, картой, пешками) и заставл€ет их действовать	
*/
#include <memory>
#include <vector>
#include "TileMap.h"

class EventController;
class Pawn;
class GameMode;

class GameController final
{
public:
	GameController();
	~GameController();
	void init(EventController & newEventController);
	void GameStep();

	void registredNewPawn(std::shared_ptr<Pawn> pawn);
private:
	std::shared_ptr<TileMap> tileMap; 
	std::shared_ptr<GameMode> gameMode;
	std::vector<std::shared_ptr<Pawn>> pawnList; 
public:
	std::shared_ptr<TileMap> getTileMap();
	std::vector<std::shared_ptr<Pawn>>& getPawnList();
};