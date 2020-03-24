#include "FollowPathBehaviour.h"
#include "Agent.h"
#include "Grass.h"

IBehaviour::Result FollowPathBehaviour::update(Agent* agent, float deltaTime)
{
	if (agent->getPath().empty())
		return SUCCESS;

	// get position of next node in path
	Vector2 target = agent->getPath().front()->position;

	// distance to node
	float xDiff = target.x - agent->getPosition().x;
	float yDiff = target.y - agent->getPosition().y;

	float distanceSqr = xDiff * xDiff + yDiff * yDiff;

	// if not at the target, move towards it
	if (distanceSqr > m_radius * m_radius)
	{
		Vector2 velocity = (target - agent->getPosition()).normalised() * agent->getMaxForce();
		Vector2 force = velocity - agent->getVelocity();

		agent->addForce(force * deltaTime);
		return ONGOING;
	}
	else
	{
		// at the node, remove it and move to the next
		agent->getPath().pop_front();
		
		// if agent has reached target node, return success
		if (agent->getPath().empty())
			return SUCCESS;
	}

	return FAILURE;
}