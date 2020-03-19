#include "SeekSteering.h"
#include "Agent.h"

Vector2 SeekSteering::getForce(Agent* agent) const
{
	Vector2 force = Vector2(0, 0);

	if (!m_target)
		return force;

	Vector2 velocity =
		(m_target->getPosition() - agent->getPosition()).normalised() * agent->getMaxForce();

	force = velocity - agent->getVelocity();

	return force;
}