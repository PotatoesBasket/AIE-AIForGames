#pragma once
#include "GameObject.h"
#include "ResourceBase.h"
#include "Tile.h"
#include <list>

class Map : public GameObject
{
public:
	Map();
	~Map() {}

	void onDraw(std::shared_ptr<aie::Renderer2D> renderer) override;

	unsigned int getTileSize() const { return m_tileSize; }
	unsigned int getMapWidth() const { return m_tileSize * m_mapCols; }
	unsigned int getMapHeight() const { return m_tileSize * m_mapRows; }

private:
	//map data
	const unsigned int m_tileSize = 72;
	const unsigned int m_mapCols = 50;
	const unsigned int m_mapRows = 50;

	std::list<std::unique_ptr<Tile>> m_tiles;

	//tileset data
	const unsigned int m_sheetCols = 2;
	const unsigned int m_sheetRows = 1;
	float m_percentWidth = 0;
	float m_percentHeight = 0;

	std::shared_ptr<ResourceBase> m_tileset;
};