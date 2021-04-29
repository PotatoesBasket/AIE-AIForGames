#include "SteeringBehaviour.h"
#include "Agent.h"
#include "DebugManager.h"

IBehaviour::Result SteeringBehaviour::update(Agent* agent, float deltaTime)
{
	for (auto& force : m_steeringForces)

		agent->addForce(force->getForce(agent) * deltaTime);

	DebugManager::current().noOfSteering++;

	return Result::SUCCESS;
}