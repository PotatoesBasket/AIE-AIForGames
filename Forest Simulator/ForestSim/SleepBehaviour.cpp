#include "SleepBehaviour.h"
#include "Agent.h"

IBehaviour::Result SleepBehaviour::update(Agent* agent, float deltaTime)
{
	agent->setVelocity(glm::vec2(0, 0));
	agent->getStats()->getEnergy().manualAdjust(-0.1f);
	return Result::SUCCESS;
}