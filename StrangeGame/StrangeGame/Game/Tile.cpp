#include "stdafx.h"
#include "Tile.h"
#include "InGamePawn.h"

//Координаты 0xCCCCCCCC что бы в отладчике было видно. Однако компиляторы и сами любят заполнять подобным мусором...
Tile::Tile() : coordinats{0xCCCCCCCC, 0xCCCCCCCC }, gameColor{ GameColor::minColor }
{

}

Tile::Tile(sf::Vector2i newCoordinats, GameColor newGameColor) : coordinats{ newCoordinats }, gameColor{newGameColor}
{

}

bool Tile::setPawn(std::weak_ptr<InGamePawn> pawn)
{
	assert(!pawn.expired());

	if (!pPawn.expired())
		return false;

	pPawn = pawn;
	auto sharedPawn = pawn.lock();
	sharedPawn->setNewCoordinats(coordinats);
}

bool Tile::clearPawn()
{
	if (pPawn.expired())
		return true;
	//Проверяем соответствие координат пешки и тайла, дабы не оставлять провисших пешек.
	auto pawn = pPawn.lock();
	if (coordinats != pawn->getCoordinats())
	{
		pPawn.reset();
		return true;
	}
	return false;
}

Tile::Tile(const Tile& other) : coordinats{ other.coordinats }, gameColor{ other.gameColor }, pPawn {other.pPawn}
{

}

Tile& Tile::operator= (const Tile& other)
{
	coordinats = other.coordinats;
	gameColor = other.gameColor;
	pPawn = other.pPawn;
	return *this;
}

Tile::Tile(Tile&& that) noexcept
{
	swap(*this, that);
}

Tile& Tile::operator= (Tile&& that) noexcept
{
	swap(*this, that);
	return *this;
}