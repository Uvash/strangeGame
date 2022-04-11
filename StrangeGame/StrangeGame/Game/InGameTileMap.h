#pragma once

/*
	����� InGameTileMap - ����� ������ TileMap ���������� �� ������� �����.
*/
#include <SFML/System.hpp>
#include <memory>
#include <vector>
class Tile;
class InGamePawn;
class InGameTileMap
{
public:
	InGameTileMap() = delete;
	InGameTileMap(sf::Vector2i newSize);
	virtual ~InGameTileMap();

	bool addPawnAtMap(std::weak_ptr<InGamePawn> pawn, sf::Vector2i targetTile);
private:
	std::vector<Tile> tiles;
	std::vector<std::weak_ptr<InGamePawn>> pawns;
	sf::Vector2i size;

	int v2iToTileAddres(sf::Vector2i vec2i);
	sf::Vector2i TileAddresToV2i(int tileAddres);

public:
	const Tile& getTile(sf::Vector2i vec2i);
	const Tile& getTile(int tileAddres);
};