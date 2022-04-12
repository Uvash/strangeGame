#pragma once
/*
	Класс игрок - вызывается гейм модом и старается сделать ход.
*/
#include "SFML/System.hpp"
enum class gameMoveStatus
{
	cannotMove = -1,	// Игрок не может сделать ход (например занял все необходимые клетки или же блокирован полностью врагом)
	dontMove,			// Игрок не двигается (ушёл пить чай)
	move,				// Игрок делает ход в startPosition и targetPosition валидные координаты

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