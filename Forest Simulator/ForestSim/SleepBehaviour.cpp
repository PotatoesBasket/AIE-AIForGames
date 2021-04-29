#include "SleepBehaviour.h"
#include "Agent.h"
#include "DebugManager.h"

IBehaviour::Result SleepBehaviour::update(Agent* agent, float deltaTime)
{
	agent->setVelocity(glm::vec2(0, 0));
	agent->getStats()->getEnergy()->currentPercent -= 0.1f;
	DebugManager::current().noOfSleeping++;
	return Result::SUCCESS;
}