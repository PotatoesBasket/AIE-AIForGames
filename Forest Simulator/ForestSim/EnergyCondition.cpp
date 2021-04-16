#include "Conditions.h"
#include "Agent.h"

// return true if energy drops below critical level
// or agent is already sleeping and hasn't hit full yet
// (will be interrupted by higher priority needs)

IBehaviour::Result EnergyCondition::update(Agent* agent, float deltaTime)
{
	if (agent->getSleepState() == false &&
		agent->getStats()->getEnergy().currentPercent >= criticalLevel)
	{
		agent->setSleepState(true);
		return Result::SUCCESS;
	}
	else if (agent->getSleepState() == true &&
		agent->getStats()->getEnergy().currentPercent > 0)
		return Result::SUCCESS;

	agent->setSleepState(false);
	return Result::FAILURE;
}