#pragma once
#include "IBehaviour.h"

class SpawnBehaviour : public IBehaviour
{
public:
	Result update(Agent* agent, float deltaTime);
};