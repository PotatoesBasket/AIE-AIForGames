#pragma once
#include "GameObject.h"
#include "ResourceBase.h"
#include "Tile.h"
#include "RNG.h"
#include "Agent.h"
#include "Grass.h"

class AABB;

class Map : public GameObject
{
public:
	Map();
	~Map() {}

	void onUpdate(float deltaTime) override;
	void onDraw(std::shared_ptr<aie::Renderer2D> renderer) override;

	Vector2 getRandomTraversablePos();
	Node* getNodeAtPosition(float xPos, float yPos);

	unsigned int getTileSize() const { return m_tileSize; }
	unsigned int getMapWidthCells() const { return m_mapCols; }
	unsigned int getMapHeightCells() const { return m_mapRows; }
	unsigned int getMapWidthPx() const { return m_tileSize * m_mapCols; }
	unsigned int getMapHeightPx() const { return m_tileSize * m_mapRows; }

	std::vector<std::unique_ptr<Tile>>& getTiles() { return m_tiles; }
	std::vector<std::unique_ptr<AABB>>& getObstacles() { return m_obstacles; }
	std::vector<std::unique_ptr<Agent>>& getBunnies() { return m_bunnies; }
	std::vector<std::unique_ptr<Agent>>& getFoxes() { return m_foxes; }
	std::vector<std::unique_ptr<Grass>>& getGrass() { return m_grassPatches; }

private:
	void loadMapData();
	void setMapConnections();
	void createObstacle(float x, float y);

private:
	//tileset data
	const unsigned int m_sheetCols = 5;
	const unsigned int m_sheetRows = 1;
	float m_percentWidth = 0;
	float m_percentHeight = 0;

	std::shared_ptr<ResourceBase> m_tileset;

	//map data
	const unsigned int m_tileSize = 72;
	unsigned int m_mapCols = 50;
	unsigned int m_mapRows = 50;

	std::vector<std::unique_ptr<Tile>> m_tiles; //nodes for pathing

	//object data
	std::vector<std::unique_ptr<AABB>> m_obstacles;
	std::vector<std::unique_ptr<Agent>> m_bunnies;
	std::vector<std::unique_ptr<Agent>> m_foxes;
	std::vector<std::unique_ptr<Grass>> m_grassPatches;
};