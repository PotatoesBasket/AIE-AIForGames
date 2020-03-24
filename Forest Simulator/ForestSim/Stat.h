#pragma once
#include "GameObject.h"

// stats are a range from 0 (min) to 100 (max)
// all animal stats start at 0
// usually, reaching 100 means they ded
// set percentage stat rises naturally every "second"

class Stat
{
public:
	Stat(float incrementPercent) : m_inc(incrementPercent) {}
	~Stat() {}

	void update(float deltaTime)
	{
		m_timer += deltaTime;

		if (m_timer >= 1.0f)
		{
			m_current += m_inc;
			m_timer = 0.0f;
		}
	}

	void reset() { m_timer = 0.0f; m_current = 0.0f; }
	void manualAdjust(float amount) { m_current += amount; }
	void manualSet(float value) { m_current = value; }

	float getCurrentPercent() { return m_current; }

private:
	float m_timer = 0.0f;
	float m_current = 0.0f;
	float m_inc = 0.0f;
};