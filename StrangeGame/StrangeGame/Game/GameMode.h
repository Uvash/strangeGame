#pragma once

/*
 Класс GameMode - взаимодействет с игроками и картой. Определяет кто ходит, и куда ходит, а так же кем и где достигнута победа. 
*/
#include <SFML/System.hpp>
#include <memory>
#include <vector>

class GameController;
class InGameTileMap;
class InGamePawn;
enum class GameColor;

class GameMode final
{
public:
	GameMode() = delete;
	GameMode(GameController& newGameController);
	~GameMode();

	void connectToTileMap(std::shared_ptr<InGameTileMap> tileMap);
	void connectToPawns(std::vector<std::shared_ptr<InGamePawn>> pawnList);

	bool addPawnInGame(sf::Vector2i coordinats, GameColor color);
	bool checkMove(sf::Vector2i start, sf::Vector2i target);
	bool movePawn(sf::Vector2i start, sf::Vector2i target);
private:
	GameController& gameController;
	std::weak_ptr<InGameTileMap> inGameTileMap;
	std::vector<std::weak_ptr<InGamePawn>> inGamePawns;
public:
	void AddPawnsAtMap();

};