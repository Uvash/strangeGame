#pragma once
/*
	����� RenderedPawn - ��������������� ����� ��� ��������� �����
*/
#include <memory>
#include <SFML/Graphics.hpp>

enum class GameColor;
class RenderedPawn
{
public:
	RenderedPawn();
	virtual ~RenderedPawn();

	sf::Sprite& getSprite();
	void createPawnSprite(sf::Image& inputImage, GameColor newGameColor);
private:
	sf::Texture pawnTexture;
	sf::Sprite pawnSprite;
};