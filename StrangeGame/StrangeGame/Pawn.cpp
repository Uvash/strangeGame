#include <stdafx.h>
#include "Pawn.h"

Pawn::Pawn(const sf::Vector2i& newCoordinats, const GameColor& newGameColor) : InGamePawn{ newCoordinats , newGameColor }, RenderedPawn{}
{

}

Pawn::~Pawn() {};