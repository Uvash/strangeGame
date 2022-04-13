#pragma once

/*
	����� RenderedTileMap - �������� �� ������ ����������� ���� ������ � ������� �������� ������� � ����� � �� �����
*/
#include <vector> 
#include <memory>
#include <SFML/Graphics.hpp>


class InGameTileMap;
class RenderedTileMap 
{
public:
	RenderedTileMap();
	virtual ~RenderedTileMap();


	sf::Sprite& getSprite();	
	void createMapTexture(sf::Image& inputImage, std::weak_ptr<InGameTileMap> inGameTileMap); //� ������������ ����������, ��� ���� ����� ������ � ���������� �� ����� ������������ Image, ��� ��� �� ������� �� ���
	void createMapSprite();
private:

	sf::Texture mapTexture;
	sf::Sprite mapSprite;	
};