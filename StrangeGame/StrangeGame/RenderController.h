#pragma once
/*
* class RenderController - контролирует рендеринг объектов
*/
#include <vector>
#include <SFML/Graphics.hpp>
enum textureName
{
	whiteTile = 0,
	blackTile,
	whitePawn,
	blackPawn,
	maxTexture
};
class RenderController final
{
public:
	RenderController(sf::RenderWindow& newWindow);
	~RenderController();
	void init();
	void updateScreen();
private:
	void loadTexture();
	sf::RenderWindow& window;
	std::vector<sf::Texture> textures;
	std::vector<sf::Sprite> sprites;
};