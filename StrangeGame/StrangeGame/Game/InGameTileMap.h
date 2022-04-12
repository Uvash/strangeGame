#pragma once

/*
	 ласс InGameTileMap - часть класса TileMap отвечающа€ за игровую карту.
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
	bool swapPawns(sf::Vector2i firstTile, sf::Vector2i secondTile);
private:
	std::vector<Tile> tiles;
	std::vector<std::weak_ptr<InGamePawn>> pawns;
	sf::Vector2i size;

	int v2iToTileAddres(sf::Vector2i vec2i);
	sf::Vector2i TileAddresToV2i(int tileAddres);

public:
	const Tile& getTile(sf::Vector2i vec2i);
	const Tile& getTile(int tileAddres);
	const sf::Vector2i& getSize();
	bool inRange(const sf::Vector2i target);
	void printMap();
};