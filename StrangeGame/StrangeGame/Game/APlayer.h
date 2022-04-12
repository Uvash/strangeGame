#pragma once
/*
	����� ����� - ���������� ���� ����� � ��������� ������� ���.
*/
#include "SFML/System.hpp"
enum class gameMoveStatus
{
	cannotMove = -1,	// ����� �� ����� ������� ��� (�������� ����� ��� ����������� ������ ��� �� ���������� ��������� ������)
	dontMove,			// ����� �� ��������� (���� ���� ���)
	move,				// ����� ������ ��� � startPosition � targetPosition �������� ����������

};
class APlayer
{
public:
	APlayer();
	APlayer(GameColor newColor);
	virtual gameMoveStatus makeMove(sf::Vector2i & startPosition, sf::Vector2i & targetPosition);
	virtual ~APlayer();

	const GameColor & getColor();
	void setColor(const GameColor& newColor);
private:
	GameColor color;
};