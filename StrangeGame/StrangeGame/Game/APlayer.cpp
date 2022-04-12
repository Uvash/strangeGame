#include <stdafx.h>
#include "APlayer.h"


APlayer::APlayer() : color{ GameColor::maxColor } {}

APlayer::APlayer(GameColor newColor) : color{ newColor } {}

gameMoveStatus APlayer::makeMove(sf::Vector2i& startPosition, sf::Vector2i& targetPosition)
{
	return gameMoveStatus::cannotMove;
}

const GameColor& APlayer::getColor()
{
	return color;
}
void APlayer::setColor(const GameColor& newColor)
{
	color = newColor;
}

APlayer::~APlayer() {}
