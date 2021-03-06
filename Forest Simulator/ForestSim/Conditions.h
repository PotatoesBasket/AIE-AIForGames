#pragma once
#include "IBehaviour.h"

class DangerCondition : public IBehaviour
{
public:
	Result update(Agent* agent, float deltaTime) override;

private:
	const float fleeRange = 200.0f;
};

class HungerCondition : public IBehaviour
{
public:
	Result update(Agent* agent, float deltaTime) override;

private:
	const float criticalLevel = 0.5f;
};

class EnergyCondition : public IBehaviour
{
public:
	Result update(Agent* agent, float deltaTime) override;

private:
	const float criticalLevel = 0.8f;
};

class MateCondition : public IBehaviour
{
public:
	Result update(Agent* agent, float deltaTime) override;
};