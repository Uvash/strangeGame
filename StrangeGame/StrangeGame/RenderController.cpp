#include "stdafx.h"
#include "RenderController.h"

RenderController::RenderController(sf::RenderWindow& newWindow) : window{ newWindow } {}

RenderController::~RenderController() {}

void RenderController::init()
{
	loadTexture();
}

void RenderController::loadTexture()
{
	sf::Image inputImage;
	//загружаем текстуру как картинку
	inputImage.loadFromFile({ "textures.bmp" });
	//превращаем розовые пиксели в прозрачные
	inputImage.createMaskFromColor({ 255 , 0 , 255 });

	textures.resize(textureName::maxTexture);
	sprites.resize(textureName::maxTexture);

	for (int i = 0; i < textureName::maxTexture; i++)
	{
		textures[i].loadFromImage(inputImage, { i * 32, 0 , 32, 32 });
		sprites[i].setTexture(textures[i]);
		sprites[i].setPosition({ i * 32.0f, i * 32.0f });
	}

}

void RenderController::updateScreen()
{
	window.clear(sf::Color::Black);
	for (auto sprite : sprites)
	{
		window.draw(sprite);
	}
	window.display();
}