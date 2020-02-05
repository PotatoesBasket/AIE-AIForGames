#pragma once
#include "IBehaviour.h"
#include "ISteering.h"
#include <memory>
#include <vector>

class SteeringBehaviour : public IBehaviour
{
public:
	SteeringBehaviour() {}
	SteeringBehaviour(std::shared_ptr<ISteering> steering) { m_steeringForces.push_back(steering); }

	Result update(GameObject* object, float deltaTime) override;

	void addSteeringForce(std::shared_ptr<ISteering> steering) { m_steeringForces.push_back(steering); }

protected:
	std::vector<std::shared_ptr<ISteering>> m_steeringForces;
};