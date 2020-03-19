#pragma once
#include "ISteering.h"

class AvoidSteering : public ISteering
{
public:
	Vector2 getForce(Agent* agent) const override;
};