#include "Conditions.h"
#include "Agent.h"

IBehaviour::Result HungerCondition::update(Agent* agent, float deltaTime)
{
	if (agent->getStats()->getHunger().currentPercent > criticalLevel)
	{
		Node* food = agent->getNearestFood();

		if (food == nullptr)
		{
			return Result::FAILURE;
		}
		else
		{
			agent->m_targetNode = food;
			return Result::SUCCESS;
		}
	}

	agent->m_targetGrass = nullptr;
	agent->m_targetNode = nullptr;
	return Result::FAILURE;
}