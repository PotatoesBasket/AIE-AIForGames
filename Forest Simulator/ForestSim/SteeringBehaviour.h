#pragma once
#include "IBehaviour.h"
#include "ISteering.h"
#include <memory>
#include <vector>

//Behaviour for adding steering forces to an agent
//Allows for multiple forces to be added together

class SteeringBehaviour : public IBehaviour
{
public:
	SteeringBehaviour() {}
	SteeringBehaviour(std::shared_ptr<ISteering> steering) { m_steeringForces.push_back(steering); }
	~SteeringBehaviour() {}

	Result update(Agent* agent, float deltaTime) override;

	void addSteeringForce(std::shared_ptr<ISteering> steering) { m_steeringForces.push_back(steering); }

protected:
	std::vector<std::shared_ptr<ISteering>> m_steeringForces;
};