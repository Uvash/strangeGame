#pragma once

/*
 ����� GameMode - �������������� � �������� � ������. ���������� ��� �����, � ���� �����, � ��� �� ��� � ��� ���������� ������. 
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
private:
	GameController& gameController;
	std::weak_ptr<InGameTileMap> inGameTileMap;
	std::vector<std::weak_ptr<InGamePawn>> inGamePawns;


};