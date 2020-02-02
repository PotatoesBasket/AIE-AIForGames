#pragma once

class Clock
{
public:
	Clock() {}
	~Clock() {}

	void update(float deltaTime) { m_seconds += deltaTime * m_multiplier; }

	int getSeconds() const { return (int)m_seconds; }
	int getMinutes() const { return (int)(getSeconds() / 60); }
	int getHours() const { return (int)(getMinutes() / 60); }
	int getDays() const { return (int)(getHours() / 24); }
	int getYears() const { return (int)(getDays() / 365); }

	float setMultiplier(float m) { m_multiplier = m; }

private:
	float m_multiplier = 1;
	float m_seconds = 0;
};