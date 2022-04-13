#pragma once

/*
	класс RenderedTileMap - отвечает за сборку объеденение всех тайлов в большую текстуру задника и вывод её на экран
*/
#include <vector> 
#include <memory>
#include <SFML/Graphics.hpp>


class InGameTileMap;
class RenderedTileMap 
{
public:
	RenderedTileMap();
	virtual ~RenderedTileMap();


	sf::Sprite& getSprite();	
	void createMapTexture(sf::Image& inputImage, std::weak_ptr<InGameTileMap> inGameTileMap); //В документации говорилось, что если нужна работа с текстурами то лучше использовать Image, так как он заточен на это
	void createMapSprite();
private:

	sf::Texture mapTexture;
	sf::Sprite mapSprite;	
};