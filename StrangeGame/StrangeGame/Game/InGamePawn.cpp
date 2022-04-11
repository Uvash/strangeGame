#include "stdafx.h"
#include "InGamePawn.h"

InGamePawn::InGamePawn(const sf::Vector2i& newCoordinats, const GameColor& newGameColor) : coordinats{ newCoordinats }, gameColor{ newGameColor }
{
	assert(coordinats.x >= 0 && coordinats.y >= 0);
	assert(gameColor >= GameColor::minColor && gameColor < GameColor::maxColor);
}

void InGamePawn::setNewCoordinats(const sf::Vector2i& newCoordinats)
{
	assert(newCoordinats.x >= 0 && newCoordinats.y >= 0);
	coordinats = newCoordinats;
}

InGamePawn::~InGamePawn()
{

}
void InGamePawn::setNewGameColor(const GameColor& newGameColor)
{
	assert(newGameColor >= GameColor::minColor && newGameColor < GameColor::maxColor);
	gameColor = newGameColor;
}

InGamePawn::InGamePawn(const InGamePawn& other) : coordinats{ other.coordinats }, gameColor{ other.gameColor }
{
	assert(coordinats.x >= 0 && coordinats.y >= 0);
	assert(gameColor >= GameColor::minColor && gameColor < GameColor::maxColor);
}

InGamePawn& InGamePawn::operator=(const InGamePawn& other)
{
	assert(other.coordinats.x >= 0 && other.coordinats.y >= 0);
	assert(other.gameColor >= GameColor::minColor && other.gameColor < GameColor::maxColor);

	coordinats = other.coordinats;
	gameColor = other.gameColor;
	return *this;
}

InGamePawn::InGamePawn(InGamePawn&& that) noexcept
{
	assert(that.coordinats.x >= 0 && that.coordinats.y >= 0);
	assert(that.gameColor >= GameColor::minColor && that.gameColor < GameColor::maxColor);
	swap(*this, that);
}

InGamePawn& InGamePawn::operator=(InGamePawn&& that) noexcept
{
	assert(that.coordinats.x >= 0 && that.coordinats.y >= 0);
	assert(that.gameColor >= GameColor::minColor && that.gameColor < GameColor::maxColor);

	swap(*this, that);
	return *this;
}