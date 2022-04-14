#include <stdafx.h>
#include "AIPlayer.h"
#include "../InGamePawn.h"

AIPlayer::AIPlayer(GameColor newColor, std::vector<std::weak_ptr<InGamePawn>> inGamePawns) : APlayer{ newColor }
{
	for (auto wPawn : inGamePawns)
	{
		if (wPawn.expired())
			continue;

		auto pawn = wPawn.lock();
		if (pawn->getGameColor() == color)
		{
			gamePawns.push_back(wPawn);
		}

	}
}

gameMoveStatus AIPlayer::makeMove(sf::Vector2i& startPosition, sf::Vector2i& targetPosition)
{
	/*
		совсем дурачка (случайная пешка случайная позиция) делать не хочется
		По этому сделаем чуть по другому: Разобьём шахматную доску на 4 чанка по 4х4. В 3-х чанках не имеющих аттрактора (победной позиции)
		Пешка сможет ходить случайно только в 2 стороны к 4-му чанку. В 4-м чанке пешка будет ходить во все 4 стороны
	*/
	//определяем адрес пешки которой будем ходить
	int pawnAddred = std::rand() % gamePawns.size();

	if(gamePawns[pawnAddred].expired())
		return gameMoveStatus::dontMove();

	auto pawn = gamePawns[pawnAddred].lock();
	sf::Vector2i offset; //в какие стороны мы будем ходить всегда
	sf::Vector2i targetChunk;
	switch (pawn->getGameColor())
	{
		//Ось Y инвертирована
		case(GameColor::white): {targetChunk = { 1, 1 }; offset = { 1, 1 }; break; }
		case(GameColor::black): {targetChunk = { 0, 0 }; offset = { -1, -1 }; break; }
	}

	sf::Vector2i pawnPos = pawn->getCoordinats();
	startPosition = pawnPos;

	sf::Vector2i chunk = { pawnPos.x / 4, pawnPos.y / 4 };

	if (chunk == targetChunk)
	{
		int direct = std::rand() % 4;
		switch (direct)
		{
			case(0): {targetPosition = { pawnPos.x + (1 * offset.x),  pawnPos.y }; break; }
			case(1): {targetPosition = { pawnPos.x,  pawnPos.y + (1 * offset.y) }; break; }
			case(2): {targetPosition = { pawnPos.x + (-1 * offset.x),  pawnPos.y }; break; }
			case(3): {targetPosition = { pawnPos.x,  pawnPos.y + (-1 * offset.y) }; break; }
		}
	}
	else
	{
		int direct = std::rand() % 2;
		switch (direct)
		{
			case(0): {targetPosition = { pawnPos.x + (1 * offset.x),  pawnPos.y }; break; }
			case(1): {targetPosition = { pawnPos.x,  pawnPos.y + (1 * offset.y) }; break; }
		}
	}
	return gameMoveStatus::move;
}

AIPlayer::~AIPlayer() {}