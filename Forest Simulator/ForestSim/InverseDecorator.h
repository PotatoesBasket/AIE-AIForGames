#pragma once
#include "Decorator.h"

class InverseDecorator : public Decorator
{
	Result update(Agent* agent, float deltaTime) override;
};