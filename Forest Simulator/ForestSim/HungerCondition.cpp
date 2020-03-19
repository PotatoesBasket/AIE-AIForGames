#include "Conditions.h"
#include "Agent.h"

IBehaviour::Result HungerCondition::update(Agent* agent, float deltaTime)
{
	// agent has reached critical hunger and isn't already eating
	if (agent->getEatState() == false &&
		agent->getStats()->getHunger().getCurrentPercent() > criticalLevel)
	{
		agent->setTargetNode(agent->getNearestFood());
		return Result::SUCCESS;
	}
	// agent is already eating and isn't full yet
	else if (agent->getEatState() == true &&
		agent->getStats()->getHunger().getCurrentPercent() > 0)
		return Result::SUCCESS;

	agent->setTargetNode(nullptr);
	return Result::FAILURE;
}