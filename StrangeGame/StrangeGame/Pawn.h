#pragma once
/*
	Класс Pawn объединяет в себе InGamePawn и RenderPawn
*/
#include "Game/InGamePawn.h"
#include "Render/RenderedPawn.h"

class Pawn : public InGamePawn , public RenderedPawn
{
public:
	Pawn() = delete;
	Pawn(const sf::Vector2i& newCoordinats, const GameColor& newGameColor);
	~Pawn() override;
};