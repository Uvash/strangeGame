#include "stdafx.h"
#include "RenderController.h"
#include "GameController.h"
#include "TileMap.h"
#include "Pawn.h"

RenderController::RenderController(sf::RenderWindow& newWindow, GameController& newGameController) : window{ newWindow }, gameController{ newGameController }, pawnList{ newGameController.getPawnList()} {}

RenderController::~RenderController() {}

void RenderController::init()
{
	tileMap = gameController.getTileMap();

	loadTexture();
	auto inGameTileMap = std::static_pointer_cast<InGameTileMap>(tileMap);
	tileMap->createMapTexture(inputImage, inGameTileMap);
	tileMap->createMapSprite();

	//��������� ����������� ��������� �� ���� �� ������ ��������� ��� ��������� �������
	scale = { 800.0f / (inGameTileMap->getSize().x * SPRITE_SIZE), 600.0f / (inGameTileMap->getSize().x * SPRITE_SIZE) };
	tileMap->getSprite().setScale(scale);

	for (auto pawn : pawnList)
	{
		pawn->createPawnSprite(inputImage, pawn->getGameColor());
		pawn->getSprite().setScale(scale);
	}
	
}

void RenderController::loadTexture()
{
	//��������� �������� ��� ��������
	inputImage.loadFromFile({ "textures.bmp" });
	//���������� ������� ������� � ����������
	inputImage.createMaskFromColor({ 255 , 0 , 255 });
}

void RenderController::updateScreen()
{
	window.clear(sf::Color::Black);
	window.draw(tileMap->getSprite());
	for (auto pawn : pawnList)
	{
		sf::Vector2i gamePos{ pawn->getCoordinats() };

		sf::Vector2f screenPos{ gamePos.x * SPRITE_SIZE * scale.x ,  gamePos.y * SPRITE_SIZE * scale.y }; //�� ������������� ��������� ����������� �� SPRITE_SIZE ��������� ���������� �������� �����, � ����������� �� ����� � ������� scale

		pawn->getSprite().setPosition(screenPos);
		window.draw(pawn->getSprite());
	}
	window.display();
}