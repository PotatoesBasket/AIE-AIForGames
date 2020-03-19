#pragma once
#include "SeekSteering.h"

class FleeSteering : public ISteering
{
public:
	Vector2 getForce(Agent* agent) const override;

	void setTarget(Agent* agent) { m_target = agent; }

protected:
	Agent* m_target = nullptr;
};