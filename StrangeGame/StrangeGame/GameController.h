#pragma once
/*
	����� GameController - ��������� ������� ������� �������� (������� ����, ������, �������) � ���������� �� �����������	
*/
#include <memory>
#include <vector>

class EventController;
class InGameTileMap;
class InGamePawn;
class GameMode;

class GameController final
{
public:
	GameController();
	~GameController();
	void init(EventController & newEventController);
	void GameStep();

	void registredNewPawn(std::shared_ptr<InGamePawn> pawn);
private:
	std::shared_ptr<InGameTileMap> tileMap; //������� ����������� ����� ��������� ����� �����
	std::shared_ptr<GameMode> gameMode;
	std::vector<std::shared_ptr<InGamePawn>> pawnList; //������� ����������� ����� ��������� ����� �����
};