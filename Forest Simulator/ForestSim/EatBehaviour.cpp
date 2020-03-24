#include "EatBehaviour.h"
#include "Agent.h"
#include "Grass.h"

IBehaviour::Result EatBehaviour::update(Agent* agent, float deltaTime)
{
	// if agent is eating another agent, set that one inactive and reset target
	if (agent->getTargetAgent() != nullptr)
	{
		// recheck agent is still active
		if (!agent->getTargetAgent()->isActive())
			return FAILURE;
		agent->getTargetAgent()->setActiveState(false);
		agent->setTargetAgent(nullptr);
	}

	// if agent is eating grass, reduce its HP and reset target
	if (agent->getTargetGrass() != nullptr)
	{
		// recheck grass is still there
		if (!agent->getTargetGrass()->isEdible())
			return FAILURE;
		agent->getTargetGrass()->reduceHP();
		agent->setTargetGrass(nullptr);
	}

	// keep agent still and reduce hunger to 0
	agent->setVelocity(Vector2(0, 0));
	agent->getStats()->getHunger().reset();

	return Result::SUCCESS;
}