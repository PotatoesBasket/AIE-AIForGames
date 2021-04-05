#include "Conditions.h"
#include "Agent.h"
#include "Map.h"
#include <glm/gtx/norm.hpp>

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
		else if (glm::length2(predator->getPosition() - agent->getPosition()) <
			glm::length2(closestPredator->getPosition() - agent->getPosition()))
			closestPredator = predator;
	}

	// check if predator is close enough to flee from
	if (closestPredator != nullptr &&
		glm::length2(closestPredator->getPosition() - agent->getPosition()) < fleeRange * fleeRange)
	{
		agent->setTargetAgent(closestPredator);
		return Result::SUCCESS;
	}

	agent->setTargetAgent(nullptr);
	return Result::FAILURE;
}