#include "FollowPathBehaviour.h"
#include "Agent.h"

IBehaviour::Result FollowPathBehaviour::update(Agent* agent, float deltaTime)
{
	if (agent->getPath().empty())
		return SUCCESS;

	// access node we're heading towards
	Vector2 target = agent->getPath().front()->position;

	// distance to node
	float xDiff = target.x - agent->getPosition().x;
	float yDiff = target.y - agent->getPosition().y;

	float distanceSqr = xDiff * xDiff + yDiff * yDiff;

	// if not at the target then move towards it
	if (distanceSqr > m_radius * m_radius)
	{
		Vector2 velocity = (target - agent->getPosition()).normalised() * agent->getMaxForce();
		Vector2 force = velocity - agent->getVelocity();

		agent->addForce(force * deltaTime);
	}
	else
	{
		// at the node, remove it and move to the next
		agent->getPath().pop_front();
	}

	return ONGOING;
}