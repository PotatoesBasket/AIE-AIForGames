#include "Map.h"
#include "RNG.h"
#include "ResourceManager.h"
#include "ScreenDefines.h"
#include "MapInfo.h"
#include "AABB.h"
#include "Bunny.h"
#include "Fox.h"
#include <fstream>

Map::Map()
{
	// load tileset .png
	m_tileset = ResourceManager::getInstance().loadTexture(TILESET);

	// set percentage of tileset one tile takes up for drawing
	m_percentWidth = 1.0f / m_sheetCols;
	m_percentHeight = 1.0f / m_sheetRows;

	loadMapData();
	setMapConnections();

	//create bunnies
	for (int i = 0; i < 2; ++i)
		m_bunnies.push_back(std::make_unique<Bunny>());

	//create foxes
	for (int i = 0; i < 2; ++i)
		m_foxes.push_back(std::make_unique<Fox>());

	//place animals on map and set their map pointers
	for (auto& bunny : m_bunnies)
	{
		bunny->setPosition(getRandomTraversablePos());
		bunny->setMap(this);
	}
	for (auto& fox : m_foxes)
	{
		fox->setPosition(getRandomTraversablePos());
		fox->setMap(this);
	}
}

void Map::onUpdate(float deltaTime)
{
	for (auto& grass : m_grassPatches)
		grass->update(deltaTime);

	for (auto& bunny : m_bunnies)
		bunny->update(deltaTime);

	for (auto& fox : m_foxes)
		fox->update(deltaTime);
}

void Map::onDraw(std::shared_ptr<aie::Renderer2D> renderer)
{
	// draw tiles
	for (auto& tile : m_tiles)
	{
		if (tile->getType() != Tile::grass)
		{
			renderer->setUVRect(
				tile->getType() * m_percentWidth,
				tile->getType() * m_percentHeight,
				m_percentWidth, m_percentHeight);
		}
		else //grass sprite is drawn seperately, so draw ground instead
		{
			renderer->setUVRect(
				Tile::ground * m_percentWidth,
				Tile::ground * m_percentHeight,
				m_percentWidth, m_percentHeight);
		} //yeah its dumb

		renderer->drawSprite(m_tileset->as<aie::Texture>(),
			tile->position.x, tile->position.y, m_tileSize, m_tileSize);
	}
	renderer->setUVRect(1, 1, 1, 1);

#ifndef NDEBUG
	// draw node connections
	renderer->setRenderColour(1, 0, 0, 1);
	for (auto& tile : m_tiles)
	{
		for (auto& edge : tile->outgoingEdges)
		{
			renderer->drawLine(tile->getPosition().x, tile->getPosition().y,
				edge.targetNode->position.x, edge.targetNode->position.y);
		}
	}
	renderer->setRenderColour(1, 1, 1, 1);

	// draw obstacle AABBs
	for (auto& obstacle : m_obstacles)
	{
		obstacle->draw(renderer);
	}
#endif

	for (auto& grass : m_grassPatches)
		grass->draw(renderer);

	for (auto& bunny : m_bunnies)
		bunny->draw(renderer);

	for (auto& fox : m_foxes)
		fox->draw(renderer);
}

Vector2 Map::getRandomTraversablePos()
{
	RNG& rng = RNG::getInstance();
	rng.setIntRange(0, m_tiles.size() - 1);

	int index = 0;

	do index = rng.nextInt();
	while (m_tiles[index]->getType() != Tile::ground);

	return m_tiles[index]->position;
}

// Gets ptr for the node located at given pixel coords
Node* Map::getNodeAtPosition(float xPos, float yPos)
{
	Node* node = nullptr;

	int x = xPos / m_tileSize;
	int y = yPos / m_tileSize;

	// return nullptr if invalid index
	if (y * m_mapCols + x > m_tiles.size())
		return nullptr;

	node = m_tiles[y * m_mapCols + x].get();
	return node;
}

// Read data from .csv file to create map
void Map::loadMapData()
{
	std::ifstream file;
	file.open(MAPINFO, std::ios::in);

	if (!file.is_open())
		throw new std::exception("map data invalid");

	int currentCol = 0;
	int currentRow = 0;

	while (true)
	{
		char tile = file.get();

		switch (tile)
		{
		//create specific tile
		case '0': //walkable ground
			m_tiles.push_back(std::make_unique<Tile>(Tile::ground,
				Vector2(currentCol * m_tileSize, (m_mapRows - currentRow) * m_tileSize)));

			++currentCol;

			continue;

		case '1': //water
			m_tiles.push_back(std::make_unique<Tile>(Tile::water,
				Vector2(currentCol * m_tileSize, (m_mapRows - currentRow) * m_tileSize)));

			createObstacle(currentCol, (m_mapRows - currentRow));

			++currentCol;

			continue;

		case '2': //tree
			m_tiles.push_back(std::make_unique<Tile>(Tile::tree,
				Vector2(currentCol * m_tileSize, (m_mapRows - currentRow) * m_tileSize)));

			createObstacle(currentCol, (m_mapRows - currentRow));

			++currentCol;

			continue;

		case '3': //edible grass
			m_tiles.push_back(std::make_unique<Tile>(Tile::grass,
				Vector2(currentCol * m_tileSize, (m_mapRows - currentRow) * m_tileSize)));

			m_grassPatches.push_back(std::make_unique<Grass>(
				Vector2(currentCol * m_tileSize, (m_mapRows - currentRow) * m_tileSize)));

			++currentCol;

			continue;

		//new row
		case '\n':
			currentCol = 0;
			++currentRow;
			continue;
		}

		if (file.peek() == EOF)
			break;
	}

	file.close();
}

// Set up graph for A* pathfinding
void Map::setMapConnections()
{
	for (int i = 0; i < m_tiles.size(); ++i)
	{
		if (m_tiles[i]->getType() == Tile::water ||
			m_tiles[i]->getType() == Tile::tree)
			continue; //tile impassable, go to next one

		bool N = false;
		bool S = false;
		bool W = false;
		bool E = false;

		//check adjacent tiles
		if (i - 1 > 0 && i % m_mapCols != 0 &&
			(m_tiles[i - 1]->getType() == Tile::ground ||
				m_tiles[i - 1]->getType() == Tile::grass))
		{
			m_tiles[i]->addEdge(m_tiles[i - 1].get());
			W = true;
		}

		if (i + 1 < m_tiles.size() && i + 1 % m_mapCols != 0 &&
			(m_tiles[i + 1]->getType() == Tile::ground ||
				m_tiles[i + 1]->getType() == Tile::grass))
		{
			m_tiles[i]->addEdge(m_tiles[i + 1].get());
			E = true;
		}

		if (i - m_mapCols > 0 &&
			(m_tiles[i - m_mapCols]->getType() == Tile::ground ||
				m_tiles[i - m_mapCols]->getType() == Tile::grass))
		{
			m_tiles[i]->addEdge(m_tiles[i - m_mapCols].get());
			N = true;
		}

		if (i + m_mapCols < m_tiles.size() &&
			(m_tiles[i + m_mapCols]->getType() == Tile::ground ||
				m_tiles[i + m_mapCols]->getType() == Tile::grass))
		{
			m_tiles[i]->addEdge(m_tiles[i + m_mapCols].get());
			S = true;
		}

		//check diagonals
		if (N && W && (m_tiles[i - m_mapCols - 1]->getType() == Tile::ground ||
			m_tiles[i - m_mapCols - 1]->getType() == Tile::grass))
			m_tiles[i]->addEdge(m_tiles[i - m_mapCols - 1].get());

		if (N && E && (m_tiles[i - m_mapCols + 1]->getType() == Tile::ground ||
			m_tiles[i - m_mapCols + 1]->getType() == Tile::grass))
			m_tiles[i]->addEdge(m_tiles[i - m_mapCols + 1].get());

		if (S && W && (m_tiles[i + m_mapCols - 1]->getType() == Tile::ground ||
			m_tiles[i + m_mapCols - 1]->getType() == Tile::grass))
			m_tiles[i]->addEdge(m_tiles[i + m_mapCols - 1].get());

		if (S && E && (m_tiles[i + m_mapCols + 1]->getType() == Tile::ground ||
			m_tiles[i + m_mapCols + 1]->getType() == Tile::grass))
			m_tiles[i]->addEdge(m_tiles[i + m_mapCols + 1].get());
	}
}

// Create tile-sized AABB around given tile coords
void Map::createObstacle(float x, float y)
{
	m_obstacles.push_back(std::make_unique<AABB>(
		Vector2(x * m_tileSize - (m_tileSize * 0.5f), y * m_tileSize - (m_tileSize * 0.5f)),
		Vector2(x * m_tileSize + m_tileSize - (m_tileSize * 0.5f), y * m_tileSize + m_tileSize - (m_tileSize * 0.5f))));
}