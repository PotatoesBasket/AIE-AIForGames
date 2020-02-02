#include "Map.h"
#include "RNG.h"
#include "ResourceManager.h"
#include "FilePaths.h"

Map::Map()
{
	m_tileset = ResourceManager::getInstance().loadTexture(TILESET1);

	m_percentWidth = 1.0f / m_sheetCols;
	m_percentHeight = 1.0f / m_sheetRows;

	for (unsigned int x = 0; x < m_mapCols; ++x)
	{
		for (unsigned int y = 0; y < m_mapRows; ++y)
		{
			m_tiles.push_back(std::make_unique<Tile>(Tile::Type::grass, Vector2(x * m_tileSize, y * m_tileSize)));
		}
	}
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