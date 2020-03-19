#include "EatBehaviour.h"
#include "Agent.h"

IBehaviour::Result EatBehaviour::update(Agent* agent, float deltaTime)
{
	// if agent is eating another agent, set that one inactive
	if (agent->getTargetAgent() != nullptr)
		agent->getTargetAgent()->setActiveState(false);

	agent->setVelocity(Vector2(0, 0));
	agent->getStats()->getEnergy().manualAdjust(-0.1f);
	return Result::SUCCESS;
}