#include "stdafx.h"
#include "InGameTileMap.h"
#include "Tile.h"

InGameTileMap::InGameTileMap(sf::Vector2i newSize) : size{ newSize }
{
	assert(size.x > 0 && size.y > 0);
	tiles.resize(newSize.x * newSize.y);
	
	sf::Vector2i gameCoords{0, 0};
	int maxColor = static_cast<int>(GameColor::maxColor); //Расплата за enum class

	for (size_t i = 0; i < tiles.size(); i++)
	{
		Tile t = Tile{ TileAddresToV2i(i),  static_cast<GameColor>(i % maxColor) };
		tiles[i] = t;
	}

}

InGameTileMap::~InGameTileMap()
{

}

bool InGameTileMap::addPawnAtMap(std::weak_ptr<InGamePawn> pawn, sf::Vector2i targetTile)
{
	assert(!pawn.expired());
	assert(targetTile.x < size.x&& targetTile.y < size.y);

	int tileAddres = v2iToTileAddres(targetTile);

	return tiles[tileAddres].setPawn(pawn);
}

int InGameTileMap::v2iToTileAddres(sf::Vector2i vec2i)
{
	assert(size.x > vec2i.x && size.y > vec2i.y);
	return size.x * vec2i.y + vec2i.x;
}
sf::Vector2i InGameTileMap::TileAddresToV2i(int tileAddres)
{
	assert(tiles.size() > tileAddres);
	return sf::Vector2i{ tileAddres % size.x, tileAddres / size.x };
}

const Tile& InGameTileMap::getTile(sf::Vector2i vec2i)
{
	int tileAddres = v2iToTileAddres(vec2i);
	return getTile(tileAddres);
}

const Tile& InGameTileMap::getTile(int tileAddres)
{
	assert(tiles.size() > tileAddres);
	return tiles[tileAddres];
}