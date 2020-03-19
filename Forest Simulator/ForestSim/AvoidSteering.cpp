#include "AvoidSteering.h"
#include "Agent.h"
#include "AABB.h"
#include "Map.h"

Vector2 AvoidSteering::getForce(Agent* agent) const
{
	Vector2 force = Vector2(0, 0);

	//calculate a vector representing how far agent can see ahead of them
	Vector2 ahead = agent->getPosition();
	Vector2 halfAhead = agent->getPosition();

	if (agent->getVelocity().x != 0 && agent->getVelocity().y != 0)
	{
		ahead = agent->getPosition() + agent->getVelocity().normalised() * agent->getVisionRange();
		halfAhead = agent->getPosition() + agent->getVelocity().normalised() * agent->getVisionRange() * 0.5f;
	}

	AABB* closestObstacle = nullptr;

	for (auto& obstacle : agent->getMap()->getObstacles())
	{
		////temporary (maybe), just kill anything that gets stuck in an obstacle lol
		//if (obstacle->isInsideBox(agent->getPosition()))
		//{
		//	agent->setActiveState(false);
		//	return force;
		//}

		if (obstacle->isInsideBox(ahead) || obstacle->isInsideBox(halfAhead))
		{
			if (closestObstacle == nullptr)
				closestObstacle = obstacle.get();
			else if ((agent->getPosition().distanceSqr(obstacle->center()) <
				agent->getPosition().distanceSqr(closestObstacle->center())))
				closestObstacle = obstacle.get();
		}
	}

	if (closestObstacle != nullptr)
	{
		Vector2 distance = ahead - closestObstacle->center();

		if (distance.x != 0 && distance.y != 0)
			force = distance.normalised() * agent->getMaxAvoidForce();
	}

	return force;
}