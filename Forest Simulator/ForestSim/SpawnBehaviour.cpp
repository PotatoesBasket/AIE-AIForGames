#include "SpawnBehaviour.h"
#include "Agent.h"
#include "Map.h"

IBehaviour::Result SpawnBehaviour::update(Agent* agent, float deltaTime)
{
	if (agent->m_targetAgent == nullptr)
		return Result::FAILURE;

	if (!agent->m_targetAgent->isActive())
		return Result::FAILURE;

	agent->setVelocity(glm::vec2(0, 0));
	agent->resetRespawnTimer();
	agent->spawnNew();
	return Result::SUCCESS;
}