#include "EatBehaviour.h"
#include "Agent.h"
#include "Grass.h"

IBehaviour::Result EatBehaviour::update(Agent* agent, float deltaTime)
{
	// if agent is eating another agent, set that one inactive and reset target
	if (agent->m_targetAgent != nullptr)
	{
		// recheck agent is still active
		if (!agent->m_targetAgent->isActive())
			return Result::FAILURE;
		agent->m_targetAgent->setActiveState(false);
		agent->m_targetAgent = nullptr;
	}

	// if agent is eating grass, reduce its HP and reset target
	if (agent->m_targetGrass != nullptr)
	{
		// recheck grass is still there
		if (!agent->m_targetGrass->isEdible())
			return Result::FAILURE;
		agent->m_targetGrass->reduceHP();
		agent->m_targetGrass = nullptr;
	}

	// keep agent still and reduce hunger to 0
	agent->setVelocity(glm::vec2(0, 0));
	agent->getStats()->getHunger().reset();

	return Result::SUCCESS;
}