#pragma once
#include "SeekSteering.h"

class FleeSteering : public ISteering
{
public:
	glm::vec2 getForce(Agent* agent) const override;
};