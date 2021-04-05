#pragma once
#include "ISteering.h"

class SeekSteering : public ISteering
{
public:
	glm::vec2 getForce(Agent* agent) const override;

	void setTarget(Agent* agent) { m_target = agent; }

protected:
	Agent* m_target = nullptr;
};