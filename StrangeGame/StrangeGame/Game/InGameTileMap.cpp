#include "stdafx.h"
#include <iostream>		//для печатанья карты в консоль
#include <cstdlib>		//для печатанья карты в консоль
#include "InGameTileMap.h"
#include "Tile.h"

InGameTileMap::InGameTileMap(sf::Vector2i newSize) : size{ newSize }
{
	assert(size.x > 0 && size.y > 0);
	tiles.resize(newSize.x * newSize.y);
	
	sf::Vector2i gameCoords{0, 0};
	int maxColor = static_cast<int>(GameColor::maxColor); //Расплата за enum class
	int minColor = static_cast<int>(GameColor::minColor);
	int currentColor = minColor;

	for (size_t i = 0; i < tiles.size(); i++)
	{

		currentColor = (i + (i / size.x) % maxColor) % maxColor; //определяем чётность строки и добавляем в качестве смещения

		Tile t = Tile{ TileAddresToV2i(i),  static_cast<GameColor>(currentColor) };
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

	if (tiles[tileAddres].setPawn(pawn))
	{
		pawns.push_back(pawn);
		return true;
	}
	return false;
}

bool InGameTileMap::swapPawns(sf::Vector2i firstTile, sf::Vector2i secondTile)
{
	if (firstTile == secondTile) //Ну самим с собой обменятся легко
		return true;

	int firstAddres = v2iToTileAddres(firstTile);
	int secondAddres = v2iToTileAddres(secondTile);

	tiles[firstAddres].swapPawns(tiles[secondAddres]);
	return true;
}
int InGameTileMap::v2iToTileAddres(sf::Vector2i vec2i)
{
	assert(size.x > vec2i.x && size.y > vec2i.y);
	return size.x * vec2i.y + vec2i.x;
}
sf::Vector2i InGameTileMap::TileAddresToV2i(int tileAddres)
{
	assert(tileAddres < tiles.size() && tileAddres >= 0 );
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

const sf::Vector2i& InGameTileMap::getSize()
{
	return size;
}

bool InGameTileMap::inRange(const sf::Vector2i target)
{
	if (target.x >= size.x || target.y >= size.y || target.x < 0 || target.y < 0)
		return false;
	return true;
}

void InGameTileMap::printMap()
{
	std::system("cls");
	for (int i = 0; i < tiles.size(); i++)
	{
		if (i % size.x == 0)
			std::cout << std::endl;

		
		std::cout << tiles[i].getTileCode();
	}
}