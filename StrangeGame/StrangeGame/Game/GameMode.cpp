#include "stdafx.h"
#include <math.h>
#include <iostream>
#include "GameMode.h"
#include "GameController.h"
#include "InGameTileMap.h"
#include "InGamePawn.h"
#include "Pawn.h"
#include "Tile.h"
#include "Players/HumanPlayer.h"

GameMode::GameMode(GameController& newGameController, EventController& NewEventController) :	gameController{ newGameController }, eventController{ NewEventController } {}

GameMode::~GameMode() {}

void GameMode::connectToTileMap(std::shared_ptr<InGameTileMap> tileMap)
{
	inGameTileMap = tileMap;
}
void GameMode::connectToPawns(std::vector<std::shared_ptr<Pawn>> pawnList)
{
	inGamePawns.clear();
	inGamePawns.resize(pawnList.size()); // �� ����� ���� ��� �������� ������ ������, ��� ��������� �������������� �����������

	for (auto pawn : pawnList)
	{
		std::weak_ptr<Pawn> wp = pawn; //����� pawnList ������ ��� �� Pawn ������������ ��� � ����������� �����, �������� ����������.
		inGamePawns.push_back(wp);
	}
}

bool GameMode::addPawnInGame(sf::Vector2i coordinats, GameColor color)
{
	//���������� ��� ��������� �������
	std::shared_ptr<Pawn> pawnCandidat = std::make_shared<Pawn>(coordinats, color);
	auto map = inGameTileMap.lock();

	if (map->addPawnAtMap({pawnCandidat}, coordinats)) //���� ������ ������� �������� �� �����
	{
		gameController.registredNewPawn(pawnCandidat); //������������ ������������
		inGamePawns.push_back({ pawnCandidat });
		return true;
	}
	
	return false;
}

bool GameMode::checkMove(sf::Vector2i start, sf::Vector2i target)
{
	if (start == target)	//��� ���� ������ �� �� ������.
		return false;

	auto map = inGameTileMap.lock();

	if (!map->inRange(start)) // �������� �� ������� ������� � ����
		return false;
	if (!map->inRange(target))
		return false;

	const Tile& targetTile = map->getTile(target); 
	const Tile& positionTile = map->getTile(start);

	if (positionTile.isFree()) //� ������ ������ ����� �� ���� ������ �� �����
		return false;

	if (!targetTile.isFree()) //������ ������ �� ����, ���� ��� ��� ���-�� ����
		return false;
	
	if (std::abs(target.x - start.x) + std::abs(target.y - start.y) <= 1) // ��������� ��������� � ���-�� ����� �� ����
		return true;

	return false;
}

int GameMode::possibleMoveCountForTile(sf::Vector2i targetTile)
{
	int moveCount{ 0 };
	//��������� ��� ��������� �������� ��� �����
	if (checkMove(targetTile, { targetTile.x + 1, targetTile.y })) moveCount++;
	if (checkMove(targetTile, { targetTile.x - 1, targetTile.y })) moveCount++;
	if (checkMove(targetTile, { targetTile.x, targetTile.y + 1 })) moveCount++;
	if (checkMove(targetTile, { targetTile.x, targetTile.y - 1 })) moveCount++;
	
	return moveCount;
}

bool GameMode::movePawn(sf::Vector2i start, sf::Vector2i target)
{
	if (!checkMove(start, target))
		return false;
	assert(!inGameTileMap.expired());
	auto map = inGameTileMap.lock();
	map->swapPawns(start, target);
	map->printMap();
}

GameStatus GameMode::checkWin()
{
	assert(!inGameTileMap.expired());
	auto map = inGameTileMap.lock();

	//�� ������ ��������� ��� ����� ������, ��� �� ������������� � ������...
	sf::Vector2i whiteTarget{ 6,6 }; 
	sf::Vector2i blackTarget{ 1,1 };
	int searchRadius = 1;
	int requstedPointsToWin = 9;
	//���������� ������� ����� � �������� ����.
	int whiteVictoryPoints{ 0 };
	int blackVictoryPoints{ 0 };
	//���������� ������������� �����. ����� � �������� ���� �� �����������.
	int whiteDrawPoints{ 0 };
	int blackDrawPoints{ 0 };

	sf::Vector2i distanceToTarget;

	for (auto weakPawn : inGamePawns)
	{
		assert(!weakPawn.expired());
		auto pawn = weakPawn.lock();
		switch (pawn->getGameColor())
		{
			case (GameColor::white): 
			{ 
				distanceToTarget = { std::abs(pawn->getCoordinats().x - whiteTarget.x) ,  std::abs(pawn->getCoordinats().y - whiteTarget.y) };
				if (distanceToTarget.x <= searchRadius && distanceToTarget.y <= searchRadius) // ����� � ���� ������
				{
					whiteVictoryPoints++;
				}
				else // ����� � �� ���� ������
				{
					if (possibleMoveCountForTile(pawn->getCoordinats()) == 0)
						whiteDrawPoints++;
				}
				break;
			}

			case (GameColor::black): 
			{
				distanceToTarget = { std::abs(pawn->getCoordinats().x - blackTarget.x) ,  std::abs(pawn->getCoordinats().y - blackTarget.y) };
				if (distanceToTarget.x <= searchRadius && distanceToTarget.y <= searchRadius) // ����� � ���� ������
				{
					blackVictoryPoints++;
				}
				else // ����� � �� ���� ������
				{
					if (possibleMoveCountForTile(pawn->getCoordinats()) == 0)
						blackDrawPoints++;
				}
				break;
			}
		default:
			break;
		}

	}
	//���� ���� � ��������� (��� ��������� �������� ����� ������ ����), ����� ������������ ����� � ������ ���� ����� ���� ����-���� ������������
	if (blackVictoryPoints == requstedPointsToWin)
		return GameStatus::BlackWin;
	if (whiteVictoryPoints == requstedPointsToWin)
		return GameStatus::WhiteWin;
	
	if (whiteVictoryPoints + whiteDrawPoints == requstedPointsToWin) //����� ����� ������� � ���� ������, � ��������� �����������.
	{
		return GameStatus::Draw;
	}
	if (blackVictoryPoints + blackDrawPoints == requstedPointsToWin)
	{
		return GameStatus::Draw;
	}

	return GameStatus::gameContinue;
}

GameStatus GameMode::getGameStatus()
{
	return gameStatus;
}
void GameMode::printGameStatus()
{
	std::cout << std::endl;
	switch (gameStatus)
	{
		case(GameStatus::gameContinue) :
		{
			std::cout << "Game Continue!" << std::endl; break;
		}
		case(GameStatus::Draw):
		{
			std::cout << "Draw!" << std::endl; break;
		}
		case(GameStatus::WhiteWin):
		{
			std::cout << "White Win!" << std::endl; break;
		}
		case(GameStatus::BlackWin):
		{
			std::cout << "Black Win" << std::endl; break;
		}
	default:
		break;
	}
}

void GameMode::sawpPlayers()
{
	currentPlayer++;
	if (currentPlayer >= players.size())
		currentPlayer = 0;
}

void GameMode::addPlayers()
{
	auto humPlayer = std::make_shared<HumanPlayer>(GameColor::white, eventController, inGameTileMap);
	players.push_back(std::static_pointer_cast<APlayer>(humPlayer));
}

void GameMode::AddPawnsAtMap() 
{
	//�� ����� ���������� �������, �� ���� ������ ������� ����� ���������� �� �����...
	addPawnInGame({ 0, 0 }, GameColor::white); addPawnInGame({ 1, 0 }, GameColor::white); addPawnInGame({ 2, 0 }, GameColor::white);
	addPawnInGame({ 0, 1 }, GameColor::white); addPawnInGame({ 1, 1 }, GameColor::white); addPawnInGame({ 2, 1 }, GameColor::white);
	addPawnInGame({ 0, 2 }, GameColor::white); addPawnInGame({ 1, 2 }, GameColor::white); addPawnInGame({ 2, 2 }, GameColor::white);

	addPawnInGame({ 5, 5 }, GameColor::black); addPawnInGame({ 6, 5 }, GameColor::black); addPawnInGame({ 7, 5 }, GameColor::black);
	addPawnInGame({ 5, 6 }, GameColor::black); addPawnInGame({ 6, 6 }, GameColor::black); addPawnInGame({ 7, 6 }, GameColor::black);
	addPawnInGame({ 5, 7 }, GameColor::black); addPawnInGame({ 6, 7 }, GameColor::black); addPawnInGame({ 7, 7 }, GameColor::black);
}

void GameMode::tick()
{
	if (gameStatus == GameStatus::gameContinue)
	{
		sf::Vector2i start;
		sf::Vector2i finish;
		if (players[currentPlayer]->makeMove(start, finish) == gameMoveStatus::move)
		{
			movePawn(start, finish);
			gameStatus = checkWin();
			sawpPlayers();
		}
		if (gameStatus != GameStatus::gameContinue)
			printGameStatus();
	}
	
}