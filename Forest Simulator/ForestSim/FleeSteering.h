#pragma once
#include "SeekSteering.h"

class FleeSteering : public ISteering
{
public:
	Vector2 getForce(Agent* agent) const override;
};