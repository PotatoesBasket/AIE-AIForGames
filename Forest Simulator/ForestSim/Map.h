#pragma once
#include "GameObject.h"
#include "ResourceBase.h"
#include "Tile.h"
#include "RNG.h"
#include "Agent.h"
#include "Grass.h"
#include "AgentPool.h"
#include "Quadtree.h"

class AABB;

class Map : public GameObject
{
public:
	Map();
	~Map() {}

	void onUpdate(float deltaTime) override;
	void onDraw(aie::Renderer2D* renderer) override;

	glm::vec2 getRandomTraversablePos();
	Node* getNodeAtPosition(glm::vec2 position);

	float getTileSize() const { return m_tileSize; }
	unsigned int getMapWidthCells() const { return m_mapCols; }
	unsigned int getMapHeightCells() const { return m_mapRows; }
	float getMapWidthPx() const { return m_tileSize * m_mapCols; }
	float getMapHeightPx() const { return m_tileSize * m_mapRows; }

	std::vector<std::unique_ptr<Tile>>& getTiles() { return m_tiles; }
	std::vector<std::unique_ptr<AABB>>& getObstacles() { return m_obstacles; }
	std::vector<std::unique_ptr<Grass>>& getGrass() { return m_grassPatches; }
	std::vector<Agent*>& getBunnies() { return m_bunnies->getAgentList(); }
	std::vector<Agent*>& getFoxes() { return m_foxes->getAgentList(); }

	AgentPool* getBunnyPool() { return m_bunnies.get(); }
	AgentPool* getFoxPool() { return m_foxes.get(); }

	Quadtree* getBunnyTree() { return m_bunnyTree.get(); }
	Quadtree* getFoxTree() { return m_foxTree.get(); }
	Quadtree* getGrassTree() { return m_grassTree.get(); }

private:
	void loadMapData();
	void setMapConnections();
	void createObstacle(float x, float y);

	void fillQuadtrees();

private:
	//tileset data
	const unsigned int m_sheetCols = 5U;
	const unsigned int m_sheetRows = 1U;
	float m_percentWidth = 0.0f;
	float m_percentHeight = 0.0f;

	std::shared_ptr<ResourceBase> m_tileset;

	//map data
	float m_tileSize = 72.0f;
	unsigned int m_mapCols = 50U;
	unsigned int m_mapRows = 50U;

	std::vector<std::unique_ptr<Tile>> m_tiles; //nodes for pathing

	//object data
	std::vector<std::unique_ptr<AABB>> m_obstacles;
	std::vector<std::unique_ptr<Grass>> m_grassPatches;

	std::unique_ptr<AgentPool> m_bunnies = nullptr;
	std::unique_ptr<AgentPool> m_foxes = nullptr;

	std::unique_ptr<Quadtree> m_bunnyTree = nullptr;
	std::unique_ptr<Quadtree> m_foxTree = nullptr;
	std::unique_ptr<Quadtree> m_grassTree = nullptr;
};