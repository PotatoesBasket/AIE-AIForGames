#include "SpawnBehaviour.h"
#include "Agent.h"
#include "Map.h"

IBehaviour::Result SpawnBehaviour::update(Agent* agent, float deltaTime)
{
	if (agent->getTargetAgent() == nullptr)
		return Result::FAILURE;

	if (!agent->getTargetAgent()->isActive())
		return Result::FAILURE;

	agent->setVelocity(glm::vec2(0, 0));
	agent->resetRespawnTimer();
	agent->spawnNew();
	return Result::SUCCESS;
}