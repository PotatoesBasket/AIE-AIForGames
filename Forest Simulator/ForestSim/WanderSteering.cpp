#include "WanderSteering.h"
#include "Agent.h"
#include "RNG.h"
#include <glm/vec2.hpp>

glm::vec2 WanderSteering::getForce(Agent* agent) const
{
	glm::vec2 force = glm::vec2(0, 0);

	RNG& rng = RNG::getInstance();

	rng.setFloatRange(-1, 1);
	float x = agent->getPosition().x + rng.nextFloat();
	float y = agent->getPosition().y + rng.nextFloat();

	glm::vec2 m_target = glm::vec2(x, y);

	glm::vec2 velocity =
		glm::normalize(m_target - agent->getPosition()) * agent->getMaxForce();

	force = velocity - agent->getVelocity();

	return force;
}