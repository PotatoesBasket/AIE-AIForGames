#include "SeekSteering.h"
#include "Agent.h"

glm::vec2 SeekSteering::getForce(Agent* agent) const
{
	glm::vec2 force = glm::vec2(0, 0);

	if (!m_target)
		return force;

	glm::vec2 velocity =
		glm::normalize(m_target->getPosition() - agent->getPosition()) * agent->getMaxForce();

	force = velocity - agent->getVelocity();

	return force;
}