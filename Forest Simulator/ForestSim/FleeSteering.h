#pragma once
#include "SeekSteering.h"

class FleeSteering : public SeekSteering
{
public:
	FleeSteering() { m_speed = -50; }

	void setSpeed(float speed) override { m_speed = -speed; }
};