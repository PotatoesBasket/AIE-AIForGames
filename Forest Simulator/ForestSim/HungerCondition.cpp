#include "Conditions.h"
#include "Agent.h"

IBehaviour::Result HungerCondition::update(Agent* agent, float deltaTime)
{
	if (agent->getStats()->getHunger().getCurrentPercent() > criticalLevel)
	{
		Node* food = agent->getNearestFood();

		if (food == nullptr)
		{
			return Result::FAILURE;
		}
		else
		{
			agent->setTargetNode(food);
			return Result::SUCCESS;
		}
	}

	agent->setTargetGrass(nullptr);
	agent->setTargetNode(nullptr);
	return Result::FAILURE;
}