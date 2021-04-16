#pragma once
#include "GameObject.h"
#include "Graph.h"
#include "AABB.h"
#include "IBehaviour.h"
#include "Life.h"
#include <list>

class Map;
struct Node;
class Grass;

// virtual class for game objects with pathfinding and behaviours
class Agent : public GameObject
{
public:
	Agent() {}
	virtual ~Agent() {}

	void update(float deltaTime) override;
	void draw(aie::Renderer2D* renderer) override;

	virtual void onUpdate(float deltaTime) {}
	virtual void onDraw(aie::Renderer2D* renderer) {}

	Life* getStats() { return m_life.get(); }

	//map
	Map* getMap() { return m_currentMap; }
	void setMap(Map* map) { m_currentMap = map; }

	Node* getCurrentNode();

	//behaviours
	void addBehaviour(IBehaviour* behaviour) { m_behaviourList.push_back(behaviour); }
	
	bool getSleepState() { return m_isSleeping; }
	void setSleepState(bool state) { m_isSleeping = state; }
	float getRespawnTimer() { return m_respawnTimer; }
	bool canSpawn() { return m_respawnTimer > m_respawnDelay && getStats()->getAge().currentPercent > m_matureAge; }
	void resetRespawnTimer() { m_respawnTimer = 0; }

	virtual void spawnNew() = 0;

	//pathing
	virtual Node* getNearestFood() = 0;
	virtual Node* getNearestMate() = 0;

	std::list<Node*>& getPath() { return m_path; }

	//movement
	void addForce(glm::vec2 force) { m_velocity += force; }

	glm::vec2 getVelocity() const { return m_velocity; }
	void setVelocity(glm::vec2 velocity) { m_velocity = velocity; }

	//stats
	float getMaxForce() const { return m_maxForce; }
	float getMaxVelocity() const { return m_maxVelocity; }
	float getVisionRange() const { return m_visionRange; }
	float getMaxAvoidForce() const { return m_maxAvoidForce; }
	float getMatureAge() const { return m_matureAge; }

private:
	void updateBehaviours();

public:
	//pathing
	Node* m_targetNode = nullptr;
	Agent* m_targetAgent = nullptr;
	Grass* m_targetGrass = nullptr;

protected:
	//map
	Map* m_currentMap = nullptr;

	//behaviours
	std::shared_ptr<Life> m_life;
	bool m_isSleeping = false;

	float m_bhTimer = 0.0f;
	float m_bhDelay = 0.1f; //amount of time before behaviours are updated again

	std::vector<IBehaviour*> m_behaviourList;

	//pathing
	std::list<Node*> m_path;

	//movement
	glm::vec2 m_velocity = glm::vec2(0.0f);

	//stats
	float m_maxVelocity = 0.0f;
	float m_maxForce = 0.0f;
	float m_visionRange = 0.0f;
	float m_maxAvoidForce = 0.0f;
	float m_matureAge = 0.0f;
	float m_respawnDelay = 0.0f;
	float m_respawnTimer = 0.0f;
};