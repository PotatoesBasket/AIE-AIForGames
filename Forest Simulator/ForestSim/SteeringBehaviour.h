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
	SteeringBehaviour(ISteering* steering) { m_steeringForces.push_back(steering); }
	~SteeringBehaviour() {}

	Result update(Agent* agent, float deltaTime) override;

	void addSteeringForce(ISteering* steering) { m_steeringForces.push_back(steering); }

protected:
	std::vector<ISteering*> m_steeringForces;
};