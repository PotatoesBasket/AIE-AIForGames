#pragma once
#include "ISteering.h"

class WanderSteering : public ISteering
{
public:
	glm::vec2 getForce(Agent* agent) const override;
};