#include <stdafx.h>
#include "RenderedPawn.h"

RenderedPawn::RenderedPawn() {}
RenderedPawn::~RenderedPawn() {}

sf::Sprite& RenderedPawn::getSprite()
{
	return pawnSprite;
}
void RenderedPawn::createPawnSprite(sf::Image& inputImage, GameColor newGameColor)
{
	int baseOffset = 32 * static_cast<int>(GameColor::maxColor);
	int colorOffset = static_cast<int>(newGameColor);
	
	pawnTexture.loadFromImage(inputImage, { baseOffset + colorOffset * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE });
	pawnSprite.setTexture(pawnTexture);
}