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
		������ ������� (��������� ����� ��������� �������) ������ �� �������
		�� ����� ������� ���� �� �������: �������� ��������� ����� �� 4 ����� �� 4�4. � 3-� ������ �� ������� ���������� (�������� �������)
		����� ������ ������ �������� ������ � 2 ������� � 4-�� �����. � 4-� ����� ����� ����� ������ �� ��� 4 �������
	*/
	//���������� ����� ����� ������� ����� ������
	int pawnAddred = std::rand() % gamePawns.size();

	if(gamePawns[pawnAddred].expired())
		return gameMoveStatus::dontMove();

	auto pawn = gamePawns[pawnAddred].lock();
	sf::Vector2i offset; //� ����� ������� �� ����� ������ ������
	sf::Vector2i targetChunk;
	switch (pawn->getGameColor())
	{
		//��� Y �������������
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