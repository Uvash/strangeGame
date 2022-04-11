#pragma once

/*
	класс InGamePawn - часть класса Pawn взаимодействующая с игровой логикой.
*/

#include <SFML/System.hpp>

enum class GameColor;
class InGamePawn
{
public:
	InGamePawn() = delete;
	InGamePawn(const sf::Vector2i & newCoordinats, const GameColor & newGameColor);
	virtual ~InGamePawn();

	void setNewCoordinats(const sf::Vector2i& newCoordinats);
	void setNewGameColor(const GameColor& newGameColor);
	const GameColor& getGameColor() { return gameColor; }
	const sf::Vector2i& getCoordinats() { return coordinats; }
private:
	sf::Vector2i coordinats;
	GameColor gameColor;

public:
	InGamePawn(const InGamePawn& other);
	InGamePawn& operator=(const InGamePawn& other);

	InGamePawn(InGamePawn&& that) noexcept;
	InGamePawn& operator=(InGamePawn&& that) noexcept;

	friend void swap(InGamePawn& lhs, InGamePawn& rhs) noexcept
	{
		std::swap(lhs.coordinats, rhs.coordinats);
		std::swap(lhs.gameColor, rhs.gameColor);
	}
};