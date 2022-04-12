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
	return true;
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
bool Tile::isFree() const
{
	if (pPawn.expired())
		return true;
	return false;
}
void Tile::swapPawns(Tile& other)
{
	std::swap(pPawn, other.pPawn);
	updatePawnInfo();
	other.updatePawnInfo();
}

void Tile::updatePawnInfo()
{
	if (!pPawn.expired())
	{
		auto pawn = pPawn.lock();
		pawn->setNewCoordinats(coordinats);
	}
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

char Tile::getTileCode()
{
	char temp = '0'; //смещениями заставим изменить код
	if (gameColor == GameColor::black)
		temp += 1;
	if (!pPawn.expired())
	{
		auto sp = pPawn.lock();
		if (sp->getGameColor() == GameColor::black)
			temp += 4;
		else
			temp += 3;
	}

	return temp;
}