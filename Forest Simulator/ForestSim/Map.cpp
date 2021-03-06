#include "Map.h"
#include "RNG.h"
#include "ResourceManager.h"
#include "ScreenDefines.h"
#include "MapInfo.h"
#include "AABB.h"
#include "Bunny.h"
#include "Fox.h"
#include <fstream>
#include "DebugManager.h"

Map::Map()
{
	// load tileset .png
	m_tileset = ResourceManager::getInstance().loadTexture(TILESET);

	// set percentage of tileset one tile takes up for drawing
	m_percentWidth = 1.0f / m_sheetCols;
	m_percentHeight = 1.0f / m_sheetRows;

	loadMapData();
	setMapConnections();

	// create bunnies for pool
	std::vector<Agent*> bunnies;
	for (int i = 0; i < 50; ++i)
	{
		bunnies.push_back(new Bunny());
		bunnies[i]->setMap(this);
		bunnies[i]->setActiveState(false);
	}
	m_bunnies = std::make_unique<AgentPool>(bunnies);

	// create foxes for pool
	std::vector<Agent*> foxes;
	for (int i = 0; i < 50; ++i)
	{
		foxes.push_back(new Fox());
		foxes[i]->setMap(this);
		foxes[i]->setActiveState(false);
	}
	m_foxes = std::make_unique<AgentPool>(foxes);

	// set active beginning number of agents
	for (int i = 0; i < 20; ++i)
		m_bunnies->activateNext(getRandomTraversablePos(), 1);

	for (int i = 0; i < 10; ++i)
		m_foxes->activateNext(getRandomTraversablePos(), 1);

	fillQuadtrees();
}

void Map::onUpdate(float deltaTime)
{
	for (auto& grass : m_grassPatches)
		grass->update(deltaTime);

	m_bunnies->update(deltaTime);
	m_foxes->update(deltaTime);

	fillQuadtrees();
}

void Map::onDraw(aie::Renderer2D* renderer)
{
	// draw tiles
	for (auto& tile : m_tiles)
	{
		if (tile->getType() != Tile::Type::grass)
		{
			renderer->setUVRect(
				(int)tile->getType() * m_percentWidth,
				(int)tile->getType() * m_percentHeight,
				m_percentWidth, m_percentHeight);
		}
		else //grass sprite is drawn seperately, so draw ground instead
		{
			renderer->setUVRect(
				(int)Tile::Type::ground * m_percentWidth,
				(int)Tile::Type::ground * m_percentHeight,
				m_percentWidth, m_percentHeight);
		} //yeah its dumb

		renderer->drawSprite(m_tileset->as<aie::Texture>(),
			tile->position.x, tile->position.y, m_tileSize, m_tileSize);
	}
	renderer->setUVRect(1, 1, 1, 1);

	if (DebugManager::current().showNodes == true)
	{
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
	}

	for (auto& grass : m_grassPatches)
		grass->draw(renderer);

	m_bunnies->draw(renderer);
	m_foxes->draw(renderer);

	m_bunnyTree->draw(renderer);
	m_foxTree->draw(renderer);
}

glm::vec2 Map::getRandomTraversablePos()
{
	RNG& rng = RNG::getInstance();
	rng.setIntRange(0, m_tiles.size() - 1);

	int index = 0;

	do index = rng.nextInt();
	while (m_tiles[index]->getType() != Tile::Type::ground);

	return m_tiles[index]->position;
}

// Gets ptr for the node located at given pixel coords
Node* Map::getNodeAtPosition(glm::vec2 position)
{
	Node* node = nullptr;

	int x = (position.x + m_tileSize * 0.5f) / m_tileSize;
	int y = (position.y - m_tileSize * 0.5f) / m_tileSize - 50;

	int index = -y * m_mapCols + x;

	// return nullptr if invalid index
	if (index > m_tiles.size())
		return nullptr;

	node = m_tiles[index].get();
	return node;
}

// Read data from .csv file to create map
void Map::loadMapData()
{
	std::ifstream file;
	file.open(MAPINFO, std::ios::in);

	if (!file.is_open())
		throw new std::exception("map data invalid");

	unsigned int currentCol = 0;
	unsigned int currentRow = 0;

	while (true)
	{
		char tile = file.get();

		switch (tile)
		{
		//create specific tile
		case '0': //walkable ground
			m_tiles.push_back(std::make_unique<Tile>(Tile::Type::ground,
				glm::vec2(currentCol * m_tileSize, (m_mapRows - currentRow) * m_tileSize)));

			++currentCol;

			continue;

		case '1': //water
			m_tiles.push_back(std::make_unique<Tile>(Tile::Type::water,
				glm::vec2(currentCol * m_tileSize, (m_mapRows - currentRow) * m_tileSize)));

			createObstacle(currentCol, (m_mapRows - currentRow));

			++currentCol;

			continue;

		case '2': //tree
			m_tiles.push_back(std::make_unique<Tile>(Tile::Type::tree,
				glm::vec2(currentCol * m_tileSize, (m_mapRows - currentRow) * m_tileSize)));

			createObstacle(currentCol, (m_mapRows - currentRow));

			++currentCol;

			continue;

		case '3': //edible grass
			m_tiles.push_back(std::make_unique<Tile>(Tile::Type::grass,
				glm::vec2(currentCol * m_tileSize, (m_mapRows - currentRow) * m_tileSize)));

			m_grassPatches.push_back(std::make_unique<Grass>(
				glm::vec2(currentCol * m_tileSize, (m_mapRows - currentRow) * m_tileSize)));

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
	for (size_t i = 0; i < m_tiles.size(); ++i)
	{
		if (m_tiles[i]->getType() == Tile::Type::water ||
			m_tiles[i]->getType() == Tile::Type::tree)
			continue; //tile impassable, go to next one

		bool N = false;
		bool S = false;
		bool W = false;
		bool E = false;

		//check adjacent tiles
		if (i - 1 > 0 && i % m_mapCols != 0
			&& (m_tiles[i - 1]->getType() == Tile::Type::ground
				|| m_tiles[i - 1]->getType() == Tile::Type::grass))
		{
			m_tiles[i]->addEdge(m_tiles[i - 1].get());
			W = true;
		}

		if (i + 1 < (int)m_tiles.size() && i + 1 % m_mapCols != 0
			&& (m_tiles[i + 1]->getType() == Tile::Type::ground
				|| m_tiles[i + 1]->getType() == Tile::Type::grass))
		{
			m_tiles[i]->addEdge(m_tiles[i + 1].get());
			E = true;
		}

		if (i - m_mapCols > 0
			&& (m_tiles[i - m_mapCols]->getType() == Tile::Type::ground
				|| m_tiles[i - m_mapCols]->getType() == Tile::Type::grass))
		{
			m_tiles[i]->addEdge(m_tiles[i - m_mapCols].get());
			N = true;
		}

		if (i + m_mapCols < m_tiles.size()
			&& (m_tiles[i + m_mapCols]->getType() == Tile::Type::ground
				|| m_tiles[i + m_mapCols]->getType() == Tile::Type::grass))
		{
			m_tiles[i]->addEdge(m_tiles[i + m_mapCols].get());
			S = true;
		}

		//check diagonals
		if (N && W && (m_tiles[i - m_mapCols - 1]->getType() == Tile::Type::ground
			|| m_tiles[i - m_mapCols - 1]->getType() == Tile::Type::grass))
			m_tiles[i]->addEdge(m_tiles[i - m_mapCols - 1].get());

		if (N && E && (m_tiles[i - m_mapCols + 1]->getType() == Tile::Type::ground
			|| m_tiles[i - m_mapCols + 1]->getType() == Tile::Type::grass))
			m_tiles[i]->addEdge(m_tiles[i - m_mapCols + 1].get());

		if (S && W && (m_tiles[i + m_mapCols - 1]->getType() == Tile::Type::ground
			|| m_tiles[i + m_mapCols - 1]->getType() == Tile::Type::grass))
			m_tiles[i]->addEdge(m_tiles[i + m_mapCols - 1].get());

		if (S && E && (m_tiles[i + m_mapCols + 1]->getType() == Tile::Type::ground
			|| m_tiles[i + m_mapCols + 1]->getType() == Tile::Type::grass))
			m_tiles[i]->addEdge(m_tiles[i + m_mapCols + 1].get());
	}
}

// Create tile-sized AABB around given tile coords
void Map::createObstacle(float x, float y)
{
	m_obstacles.push_back(std::make_unique<AABB>(
		glm::vec2(x * m_tileSize - (m_tileSize * 0.5f), y * m_tileSize - (m_tileSize * 0.5f)),
		glm::vec2(x * m_tileSize + m_tileSize - (m_tileSize * 0.5f), y * m_tileSize + m_tileSize - (m_tileSize * 0.5f))));
}

void Map::fillQuadtrees()
{
	m_bunnyTree = std::make_unique<Quadtree>(
		AABB(glm::vec2(0.0f), glm::vec2(getMapWidthPx(), getMapHeightPx())), 1);

	for (auto& bunny : getBunnyPool()->getAgentList())
	{
		if (bunny->isActive())
			m_bunnyTree->insert(bunny);
	}

	m_foxTree = std::make_unique<Quadtree>(
		AABB(glm::vec2(0.0f), glm::vec2(getMapWidthPx(), getMapHeightPx())), 1);

	for (auto& fox : getFoxPool()->getAgentList())
	{
		if (fox->isActive())
			m_foxTree->insert(fox);
	}

	m_grassTree = std::make_unique<Quadtree>(
		AABB(glm::vec2(0.0f), glm::vec2(getMapWidthPx(), getMapHeightPx())), 1);
	
	for (auto& grass : m_grassPatches)
	{
		if (grass->isEdible())
			m_grassTree->insert(grass.get());
	}
}