#pragma once
#include "GameObject.h"
#include "Graph.h"
#include "AABB.h"
#include "IBehaviour.h"
#include "Life.h"
#include <list>

class Map;
class Node;
class Grass;

// virtual class for game objects with pathfinding and behaviours
class Agent : public GameObject
{
public:
	Agent() {}
	virtual ~Agent() {}

	void update(float deltaTime) override;

	virtual void onUpdate(float deltaTime) {}
	virtual void onDraw(std::shared_ptr<aie::Renderer2D> renderer) {}

	Life* getStats() { return m_life.get(); }

	//map
	Map* getMap() { return m_currentMap; }
	void setMap(Map* map) { m_currentMap = map; }

	Node* getCurrentNode();

	//behaviours
	void addBehaviour(IBehaviour* behaviour) { m_behaviourList.push_back(behaviour); }
	
	bool getSleepState() { return isSleeping; }
	void setSleepState(bool state) { isSleeping = state; }
	float getRespawnTimer() { return m_respawnTimer; }
	bool canSpawn() { return m_respawnTimer > m_respawnDelay && getStats()->getAge().getCurrentPercent() > m_matureAge; }
	void resetRespawnTimer() { m_respawnTimer = 0; }

	virtual void spawnNew() = 0;

	//pathing
	Node* getTargetNode() { return m_targetNode; }
	Agent* getTargetAgent() { return m_targetAgent; }
	Grass* getTargetGrass() { return m_targetGrass; }
	void setTargetNode(Node* node) { m_targetNode = node; }
	void setTargetAgent(Agent* agent) { m_targetAgent = agent; }
	void setTargetGrass(Grass* grass) { m_targetGrass = grass; }

	virtual Node* getNearestFood() = 0;
	virtual Node* getNearestMate() = 0;

	std::list<Node*>& getPath() { return m_path; }

	void addForce(glm::vec2 force) { m_velocity += force; }

	glm::vec2 getVelocity() const { return m_velocity; }
	void setVelocity(glm::vec2 velocity) { m_velocity = velocity; }

	float getMaxForce() const { return m_maxForce; }
	float getMaxVelocity() const { return m_maxVelocity; }
	float getVisionRange() const { return m_visionRange; }
	float getMaxAvoidForce() const { return m_maxAvoidForce; }
	float getMatureAge() const { return m_matureAge; }

private:
	void updateBehaviours();

protected:
	//map
	Map* m_currentMap = nullptr;

	//behaviours
	std::shared_ptr<Life> m_life;
	bool isSleeping = false;

	float m_bhTimer = 0;
	float m_bhDelay = 0.1f; //amount of time before behaviours are updated again

	std::vector<IBehaviour*> m_behaviourList;

	//pathing
	Node* m_targetNode = nullptr;
	Agent* m_targetAgent = nullptr;
	Grass* m_targetGrass = nullptr;

	std::list<Node*> m_path;

	glm::vec2 m_velocity;

	float m_maxVelocity = 0;
	float m_maxForce = 0;
	float m_visionRange = 0;
	float m_maxAvoidForce = 0;
	float m_matureAge = 0;
	float m_respawnDelay = 0;
	float m_respawnTimer = 0;
};