#pragma once
/*
	�����  TileMap - ������� ����� ������� �� InGameTileMap ���������� �� ������������� ������ � RenderedTileMap ����������� �� �������
*/
#include <SFML/System.hpp>
#include "Game/InGameTileMap.h"
#include "Render/RenderedTileMap.h"

class TileMap : public InGameTileMap, public RenderedTileMap
{
public:
	TileMap() = delete;
	TileMap(sf::Vector2i mapSize);
	~TileMap() override;
	void init();
};