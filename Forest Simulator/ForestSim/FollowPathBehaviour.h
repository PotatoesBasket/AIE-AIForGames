#pragma once
#include "IBehaviour.h"

class Agent;

// a behaviour that follows a path
class FollowPathBehaviour : public IBehaviour
{
public:
	Result update(Agent* agent, float deltaTime) override;

	void setArriveRadius(float radius) { m_radius = radius; }

private:
	float m_radius = 50;
};