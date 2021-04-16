#include "Conditions.h"
#include "Agent.h"
#include "Map.h"
#include <glm/gtx/norm.hpp>

IBehaviour::Result DangerCondition::update(Agent* agent, float deltaTime)
{
	std::vector<GameObject*> nearestFoxList;
	Quadtree* foxTree = agent->getMap()->getFoxTree();
	foxTree->query(agent->getPosition(), fleeRange, nearestFoxList);

	Agent* closestPredator = nullptr;

	// find closest predator
	for (auto& predator : nearestFoxList)
	{
		// skip if inactive
		if (!predator->isActive())
			continue;

		// if no closest is set yet, set it and skip comparison
		if (closestPredator == nullptr)
			closestPredator = dynamic_cast<Agent*>(predator);
		// otherwise, compare with current closest
		else if (glm::length2(predator->getPosition() - agent->getPosition()) <
			glm::length2(closestPredator->getPosition() - agent->getPosition()))
			closestPredator = dynamic_cast<Agent*>(predator);
	}

	// check if predator is close enough to flee from
	// probably redundant since adding quadtrees, check later
	if (closestPredator != nullptr &&
		glm::length2(closestPredator->getPosition() - agent->getPosition()) < fleeRange * fleeRange)
	{
		agent->m_targetAgent = closestPredator;
		return Result::SUCCESS;
	}

	agent->m_targetAgent = nullptr;
	return Result::FAILURE;
}