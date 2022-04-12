#pragma once
/*
	класс GameController - управляет памятью игровых объёктов (режимом игры, картой, пешками) и заставляет их действовать	
*/
#include <memory>
#include <vector>

class EventController;
class InGameTileMap;
class InGamePawn;
class GameMode;

class GameController final
{
public:
	GameController();
	~GameController();
	void init(EventController & newEventController);
	void GameStep();

	void registredNewPawn(std::shared_ptr<InGamePawn> pawn);
private:
	std::shared_ptr<InGameTileMap> tileMap; //Допишем графическую часть подключим общий класс
	std::shared_ptr<GameMode> gameMode;
	std::vector<std::shared_ptr<InGamePawn>> pawnList; //Допишем графическую часть подключим общий класс
};