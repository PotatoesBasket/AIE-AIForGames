#pragma once
#include "IBehaviour.h"

class DangerCondition : public IBehaviour
{
public:
	Result update(Agent* agent, float deltaTime) override;

private:
	const float fleeRange = 20.0f;
};

class HungerCondition : public IBehaviour
{
public:
	Result update(Agent* agent, float deltaTime) override;

private:
	const float criticalLevel = 0;// 0.5f;
};

class EnergyCondition : public IBehaviour
{
public:
	Result update(Agent* agent, float deltaTime) override;

private:
	const float criticalLevel = 0.8f;
};