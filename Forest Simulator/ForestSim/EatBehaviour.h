#pragma once
#include "IBehaviour.h"

class EatBehaviour : public IBehaviour
{
public:
	Result update(Agent* agent, float deltaTime);
};