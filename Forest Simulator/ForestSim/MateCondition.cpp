#include "Conditions.h"
#include "Agent.h"

IBehaviour::Result MateCondition::update(Agent* agent, float deltaTime)
{
	if (agent->getStats()->getAge()->currentPercent > agent->getMatureAge() && agent->canSpawn())
	{
		Node* mate = agent->getNearestMate();

		if (mate == nullptr)
		{
			return Result::FAILURE;
		}
		else
		{
			agent->m_targetNode = mate;
			return Result::SUCCESS;
		}
	}

	agent->m_targetGrass = nullptr;
	agent->m_targetNode = nullptr;
	return Result::FAILURE;
}