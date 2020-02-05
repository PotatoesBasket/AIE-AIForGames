#pragma once
#include "ISteering.h"

class SeekSteering : public ISteering
{
public:
	virtual void setSpeed(float speed) { m_speed = speed; }

	Vector2 getForce(GameObject* object) const override;

	void SetTarget(GameObject* object) { m_target = object; }

protected:
	float m_speed = 50;
	GameObject* m_target = nullptr;
};