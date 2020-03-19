#pragma once
#include "ISteering.h"

class WanderSteering : public ISteering
{
public:
	Vector2 getForce(Agent* agent) const override;
};