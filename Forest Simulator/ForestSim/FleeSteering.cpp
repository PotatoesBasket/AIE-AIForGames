#include "FleeSteering.h"
#include "Agent.h"

Vector2 FleeSteering::getForce(Agent* agent) const
{
	Vector2 force = Vector2(0, 0);

	if (!m_target)
		return force;

	Vector2 velocity =
		(m_target->getPosition() - agent->getPosition()).normalised() * -agent->getMaxVelocity();

	force = velocity - agent->getVelocity();

	return force;
}