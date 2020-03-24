#include "Conditions.h"
#include "Agent.h"
#include "Map.h"

IBehaviour::Result DangerCondition::update(Agent* agent, float deltaTime)
{
	Agent* closestPredator = nullptr;

	// find closest predator
	for (auto& predator : agent->getMap()->getFoxes())
	{
		// skip if inactive
		if (!predator->isActive())
			continue;

		// if no closest is set yet, set it and skip comparison
		if (closestPredator == nullptr)
			closestPredator = predator;
		// otherwise, compare with current closest
		else if (agent->getPosition().distanceSqr(predator->getPosition()) <
			agent->getPosition().distanceSqr(closestPredator->getPosition()))
			closestPredator = predator;
	}

	// check if predator is close enough to flee from
	if (closestPredator != nullptr &&
		agent->getPosition().distanceSqr(closestPredator->getPosition()) < fleeRange * fleeRange)
	{
		agent->setTargetAgent(closestPredator);
		return Result::SUCCESS;
	}

	agent->setTargetAgent(nullptr);
	return Result::FAILURE;
}