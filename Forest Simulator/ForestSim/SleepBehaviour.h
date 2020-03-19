#pragma once
#include "IBehaviour.h"

class SleepBehaviour : public IBehaviour
{
public:
	Result update(Agent* agent, float deltaTime);
};