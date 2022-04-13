#include <stdafx.h>
#include "RenderedTileMap.h"
#include "Game/InGameTileMap.h"
#include "Game/Tile.h"

RenderedTileMap::RenderedTileMap() {}
RenderedTileMap::~RenderedTileMap() {}

sf::Sprite& RenderedTileMap::getSprite()
{ 
	return mapSprite;
}

void RenderedTileMap::createMapTexture(sf::Image& inputImage, std::weak_ptr<InGameTileMap> inGameTileMap)
{
	assert(!inGameTileMap.expired());
	auto gameTileMap = inGameTileMap.lock();
	sf::Vector2i mapSize = gameTileMap->getSize();

	sf::Image mapImage{};
	mapImage.create( mapSize.x * SPRITE_SIZE , mapSize.y * SPRITE_SIZE);

	for (int height = 0; height < mapSize.y; height++) //итераторы было бы правильнее, но трогать std::distance не хочется
	{
		for (int width = 0; width < mapSize.x; width++)
		{
			//Получаем внутреигровой "цвет" тайла
			GameColor color = gameTileMap->getTile({ width , height }).getColor();
			int colorOffset = static_cast<int>(color);
			mapImage.copy(inputImage, width * SPRITE_SIZE, height * SPRITE_SIZE, { colorOffset * SPRITE_SIZE, 0, colorOffset * SPRITE_SIZE + SPRITE_SIZE, colorOffset * SPRITE_SIZE + SPRITE_SIZE });
		}
	}

	mapTexture.loadFromImage(mapImage);
}

void RenderedTileMap::createMapSprite()
{
	assert(mapTexture.getSize().x > 0 && mapTexture.getSize().y > 0);
	mapSprite.setTexture(mapTexture);
}