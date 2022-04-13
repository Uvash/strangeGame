#pragma once
/*
* class RenderController - контролирует рендеринг объектов
*/
#include <vector>
#include <SFML/Graphics.hpp>
class GameController;
class TileMap;
class Pawn;
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
	RenderController(sf::RenderWindow& newWindow, GameController& newGameController);
	~RenderController();
	void init();
	void updateScreen();
private:
	void loadTexture();
	sf::Vector2f scale;
	GameController& gameController;
	sf::RenderWindow& window;
	sf::Image inputImage;

	std::shared_ptr<TileMap> tileMap;
	std::vector<std::shared_ptr<Pawn>> & pawnList;
};