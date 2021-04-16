#pragma once
#include "GameObject.h"

// stats are a range from 0 (min) to 100 (max)
// all animal stats start at 0
// usually, reaching 100 means they ded
// set percentage stat rises naturally every "second"

class Stat
{
public:
	Stat() {}
	Stat(float incrementPercent) : m_inc(incrementPercent) {}
	~Stat() {}

	void update(float deltaTime);
	void reset() { m_timer = 0.0f; m_current = 0.0f; }
	void setIncrementPercent(float value) { m_inc = value; }

public:
	float currentPercent = 0.0f;

private:
	float m_timer = 0.0f;
	float m_current = 0.0f;
	float m_inc = 0.0f;
};

// class for holding all animal stats for simulating life
class Life : public Component
{
public:
	Life(float ageRate, float hungerRate, float energyRate);
	virtual ~Life() {}

	void update(GameObject* parent, float deltaTime) override;
	void draw(GameObject* parent, aie::Renderer2D* renderer) override;

	void reset();

	Stat& getAge() { return m_age; }
	Stat& getHunger() { return m_hunger; }
	Stat& getEnergy() { return m_energy; }

private:
	Stat m_age;
	Stat m_hunger;
	Stat m_energy;
};