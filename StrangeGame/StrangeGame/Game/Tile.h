#pragma once
/*
	Класс Tile - содержит информацию о тайле. Управляется через InGameTileMap. 
	Старается изображать из себя двумерный массив, являясь одномерным
*/
#include <memory>
#include <SFML/System.hpp>

class InGamePawn;
enum class GameColor;
class Tile final
{
public:	
	Tile();
	Tile(sf::Vector2i newCoordinats, GameColor newGameColor);
	~Tile() = default;
	bool setPawn(std::weak_ptr<InGamePawn> pawn);
	bool clearPawn();
	bool isFree() const;
	void swapPawns(Tile& other);
	void updatePawnInfo();
private:
	sf::Vector2i coordinats;
	GameColor gameColor;
	std::weak_ptr<InGamePawn> pPawn;

public:
	Tile(const Tile& other);
	Tile& operator= (const Tile& other);

	Tile(Tile&& that) noexcept;
	Tile& operator= (Tile&& that) noexcept;

	friend void swap(Tile& lhs, Tile& rhs) noexcept
	{
		std::swap(lhs.coordinats, rhs.coordinats);
		std::swap(lhs.gameColor, rhs.gameColor);
		std::swap(lhs.pPawn, rhs.pPawn);
	}

	char getTileCode(); //для показа в консоль, удалить если не надо.
	const GameColor& getColor() const;
};
