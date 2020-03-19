#include "WanderSteering.h"
#include "Agent.h"
#include "RNG.h"
#include <glm/vec2.hpp>

Vector2 WanderSteering::getForce(Agent* agent) const
{
	Vector2 force = Vector2(0, 0);

	RNG& rng = RNG::getInstance();

	rng.setFloatRange(-1, 1);
	float x = agent->getPosition().x + rng.nextFloat();
	float y = agent->getPosition().y + rng.nextFloat();

	Vector2 m_target = Vector2(x, y);

	Vector2 velocity =
		(m_target - agent->getPosition()).normalised() * agent->getMaxForce();

	force = velocity - agent->getVelocity();

	return force;
}