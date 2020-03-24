#include "Conditions.h"
#include "Agent.h"

IBehaviour::Result MateCondition::update(Agent* agent, float deltaTime)
{
	if (agent->getStats()->getAge().getCurrentPercent() > agent->getMatureAge() && agent->canSpawn())
	{
		Node* mate = agent->getNearestMate();

		if (mate == nullptr)
		{
			return Result::FAILURE;
		}
		else
		{
			agent->setTargetNode(mate);
			return Result::SUCCESS;
		}
	}

	agent->setTargetGrass(nullptr);
	agent->setTargetNode(nullptr);
	return Result::FAILURE;
}