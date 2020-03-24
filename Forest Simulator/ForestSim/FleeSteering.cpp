#include "FleeSteering.h"
#include "Agent.h"

Vector2 FleeSteering::getForce(Agent* agent) const
{
	Vector2 force = Vector2(0, 0);
	Vector2 velocity = Vector2(0, 0);
	Agent* target = agent->getTargetAgent();

	if (!target)
		return force;

	velocity = target->getPosition() - agent->getPosition();

	if (velocity.x == 0 && velocity.y == 0)
		velocity = Vector2(1, 1) * agent->getMaxForce(); // failsafe for if agents are in the same position
	else
		velocity = velocity.normalised() * -agent->getMaxForce();

	force = velocity - agent->getVelocity();

	return force;
}