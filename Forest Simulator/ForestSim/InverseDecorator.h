#pragma once
#include "Decorator.h"

class InverseDecorator : public Decorator
{
	Result update(GameObject* object, float deltaTime) override;
};