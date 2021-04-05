#pragma once
#include <glm/vec2.hpp>

class Agent;

//Base for all steering forces

class ISteering
{
public:
	virtual glm::vec2 getForce(Agent* agent) const = 0;
};