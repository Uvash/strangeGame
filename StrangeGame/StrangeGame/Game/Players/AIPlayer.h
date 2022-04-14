#pragma once
/*
	����� AIPlayer - ��������� ������
*/
#include <cstdlib> //��� �������
#include <vector>
#include <memory>
#include "../APlayer.h"


class InGamePawn;
class AIPlayer : public APlayer
{
public:
	AIPlayer(GameColor newColor, std::vector<std::weak_ptr<InGamePawn>> inGamePawns);
	gameMoveStatus makeMove(sf::Vector2i& startPosition, sf::Vector2i& targetPosition) override;
	~AIPlayer() override;
protected:
	std::vector<std::weak_ptr<InGamePawn>> gamePawns;
};
