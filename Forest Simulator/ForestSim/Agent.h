#pragma once
#include "GameObject.h"
#include "Graph.h"
#include "AABB.h"
#include "Life.h"
#include <list>

class Map;
class IBehaviour;
class Node;

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
	void addBehaviour(std::shared_ptr<IBehaviour> behaviour) { m_behaviourList.push_back(behaviour); }
	
	bool getEatState() { return isEating; }
	void setEatState(bool state) { isEating = state; }
	bool getSleepState() { return isSleeping; }
	void setSleepState(bool state) { isSleeping = state; }

	//pathing
	Node* getTargetNode() { return m_targetNode; }
	Agent* getTargetAgent() { return m_targetAgent; }
	void setTargetNode(Node* node) { m_targetNode = node; }
	void setTargetAgent(Agent* agent) { m_targetAgent = agent; }

	Node* getNearestWater();
	virtual Node* getNearestFood() = 0;
	virtual Node* getNearestMate() = 0;

	std::list<Node*>& getPath() { return m_path; }
	void setPath(const std::list<Node*> path) { m_path = path; }

	void addForce(Vector2 force) { m_velocity += force; }

	Vector2 getVelocity() const { return m_velocity; }
	void setVelocity(Vector2 velocity) { m_velocity = velocity; }

	float getMaxForce() const { return m_maxForce; }
	float getMaxVelocity() const { return m_maxVelocity; }
	float getVisionRange() const { return m_visionRange; }
	float getMaxAvoidForce() const { return m_maxAvoidForce; }
	float getFleeRange() const { return m_fleeRange; }

private:
	void updateBehaviours();

protected:
	//map
	Map* m_currentMap = nullptr;

	//behaviours
	std::shared_ptr<Life> m_life;
	bool isDrinking = false;
	bool isEating = false;
	bool isSleeping = false;

	float m_bhTimer = 0;
	float m_bhDelay = 0.1f; //amount of time before behaviours are updated again

	std::vector<std::shared_ptr<IBehaviour>> m_behaviourList;

	//pathing
	Node* m_targetNode = nullptr;
	Agent* m_targetAgent = nullptr;

	std::list<Node*> m_path;

	Vector2 m_velocity;

	float m_maxVelocity = 0;
	float m_maxForce = 0;
	float m_visionRange = 0;
	float m_maxAvoidForce = 0;
	float m_fleeRange = 0;
};