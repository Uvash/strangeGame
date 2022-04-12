#pragma once

/*
 ����� GameMode - �������������� � �������� � ������. ���������� ��� �����, � ���� �����, � ��� �� ��� � ��� ���������� ������. 
*/
#include <SFML/System.hpp>
#include <memory>
#include <vector>

class GameController;
class EventController;
class InGameTileMap;
class InGamePawn;
class APlayer;
enum class GameColor;

class GameMode final
{
public:
	GameMode() = delete;
	GameMode(GameController& newGameController, EventController& NewEventController);
	~GameMode();

	void connectToTileMap(std::shared_ptr<InGameTileMap> tileMap);
	void connectToPawns(std::vector<std::shared_ptr<InGamePawn>> pawnList);

	bool addPawnInGame(sf::Vector2i coordinats, GameColor color);
	bool checkMove(sf::Vector2i start, sf::Vector2i target);
	bool movePawn(sf::Vector2i start, sf::Vector2i target);
	
private:

	EventController& eventController;
	GameController& gameController;
	std::weak_ptr<InGameTileMap> inGameTileMap;
	std::vector<std::weak_ptr<InGamePawn>> inGamePawns;
	std::vector<std::shared_ptr<APlayer>> players;
public:
	void addPlayers();
	void AddPawnsAtMap();

	void tick();
};