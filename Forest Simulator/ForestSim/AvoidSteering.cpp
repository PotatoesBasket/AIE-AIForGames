#include "AvoidSteering.h"
#include "Agent.h"
#include "AABB.h"
#include "Map.h"
#include <glm/gtx/norm.hpp>

glm::vec2 AvoidSteering::getForce(Agent* agent) const
{
	glm::vec2 force = glm::vec2(0, 0);

	//calculate a vector representing how far agent can see ahead of them
	glm::vec2 ahead = agent->getPosition();
	glm::vec2 halfAhead = agent->getPosition();

	if (agent->getVelocity().x != 0 && agent->getVelocity().y != 0)
	{
		ahead = agent->getPosition() + glm::normalize(agent->getVelocity()) * agent->getVisionRange();
		halfAhead = agent->getPosition() + glm::normalize(agent->getVelocity()) * agent->getVisionRange() * 0.5f;
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

		if (obstacle->containsPoint(ahead) || obstacle->containsPoint(halfAhead))
		{
			if (closestObstacle == nullptr)
				closestObstacle = obstacle.get();
			else if (glm::length2(obstacle->center() - agent->getPosition()) < glm::length2(closestObstacle->center() - agent->getPosition()))
				closestObstacle = obstacle.get();
		}
	}

	if (closestObstacle != nullptr)
	{
		glm::vec2 distance = ahead - closestObstacle->center();

		if (distance.x != 0 && distance.y != 0)
			force = glm::normalize(distance) * agent->getMaxAvoidForce();
	}

	return force;
}