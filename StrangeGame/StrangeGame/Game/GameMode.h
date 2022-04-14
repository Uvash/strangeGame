#pragma once

/*
 Класс GameMode - взаимодействет с игроками и картой. Определяет кто ходит, и куда ходит, а так же кем и где достигнута победа. 
*/
#include <SFML/System.hpp>
#include <memory>
#include <vector>

class GameController;
class EventController;
class InGameTileMap;
class InGamePawn;
class Pawn;
class APlayer;
enum class GameColor;
enum class GameStatus
{
	gameContinue,
	Draw,
	WhiteWin,
	BlackWin
};
class GameMode final
{
public:
	GameMode() = delete;
	GameMode(GameController& newGameController, EventController& NewEventController);
	~GameMode();

	void connectToTileMap(std::shared_ptr<InGameTileMap> tileMap);
	void connectToPawns(std::vector<std::shared_ptr<Pawn>> pawnList);

	bool addPawnInGame(sf::Vector2i coordinats, GameColor color);
	bool checkMove(sf::Vector2i start, sf::Vector2i target);
	int possibleMoveCountForTile(sf::Vector2i targetTile);
	bool movePawn(sf::Vector2i start, sf::Vector2i target);
	void sawpPlayers();

	GameStatus checkWin();
	GameStatus getGameStatus();
	void printGameStatus(); 
private:

	EventController& eventController;
	GameController& gameController;
	std::weak_ptr<InGameTileMap> inGameTileMap;
	std::vector<std::weak_ptr<InGamePawn>> inGamePawns;
	int currentPlayer = 0;
	std::vector<std::shared_ptr<APlayer>> players;
	GameStatus gameStatus = GameStatus::gameContinue();
public:

	void addPlayers();
	void AddPawnsAtMap();

	void tick();
};