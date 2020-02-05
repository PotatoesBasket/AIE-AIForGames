#include "Map.h"
#include "RNG.h"
#include "ResourceManager.h"
#include "FilePaths.h"
#include <fstream>

Map::Map()
{
	m_tileset = ResourceManager::getInstance().loadTexture(TILESET);

	m_percentWidth = 1.0f / m_sheetCols;
	m_percentHeight = 1.0f / m_sheetRows;

	loadMap();
}

void Map::onDraw(std::shared_ptr<aie::Renderer2D> renderer)
{
	std::list<std::unique_ptr<Tile>>::iterator it = m_tiles.begin();

	for (unsigned int x = 0; x < m_mapCols; ++x)
	{
		for (unsigned int y = 0; y < m_mapRows; ++y)
		{
			renderer->setUVRect(
				(*it)->getType() * m_percentWidth,
				(*it)->getType() * m_percentHeight,
				m_percentWidth, m_percentHeight);

			renderer->drawSpriteTransformed3x3(m_tileset->as<aie::Texture>(),
				(*it)->getGlobalTransformFloat(), m_tileSize, m_tileSize);

			++it;
		}
	}

	renderer->setUVRect(1, 1, 1, 1);
}

void Map::loadMap()
{
	std::ifstream file;
	file.open(MAPINFO, std::ios::in);

	if (!file.is_open())
		throw new std::exception("map data invalid");

	int currentCol = 0;

	while (true)
	{
		char tile = file.get();

		switch (tile)
		{
		case '0':
			m_tiles.push_back(std::make_unique<Tile>(Tile::Type::grass,
				Vector2(currentCol * m_tileSize, m_mapRows * m_tileSize)));

			++currentCol;
			if (m_mapRows == 0)
				++m_mapCols;

			continue;

		case '1':
			m_tiles.push_back(std::make_unique<Tile>(Tile::Type::water,
				Vector2(currentCol * m_tileSize, m_mapRows * m_tileSize)));

			++currentCol;
			if (m_mapRows == 0)
				++m_mapCols;

			continue;

		case '\n':
			currentCol = 0;
			++m_mapRows;
			continue;
		}

		if (file.peek() == EOF)
			break;
	}

	file.close();
}