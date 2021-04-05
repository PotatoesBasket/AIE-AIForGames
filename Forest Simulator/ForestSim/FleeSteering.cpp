#include "FleeSteering.h"
#include "Agent.h"

glm::vec2 FleeSteering::getForce(Agent* agent) const
{
	glm::vec2 force = glm::vec2(0, 0);
	glm::vec2 velocity = glm::vec2(0, 0);
	Agent* target = agent->getTargetAgent();

	if (!target)
		return force;

	velocity = target->getPosition() - agent->getPosition();

	if (velocity.x == 0 && velocity.y == 0)
		velocity = glm::vec2(1, 1) * agent->getMaxForce(); // failsafe for if agents are in the same position
	else
		velocity = glm::normalize(velocity) * -agent->getMaxForce();

	force = velocity - agent->getVelocity();

	return force;
}