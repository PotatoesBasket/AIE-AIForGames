#pragma once
#include "ISteering.h"

class AvoidSteering : public ISteering
{
public:
	glm::vec2 getForce(Agent* agent) const override;
};