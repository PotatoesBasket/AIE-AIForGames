#pragma once
#ifndef NDEBUG
#include <Debug/MathLibrary.h>
#else
#include <Release/MathLibrary.h>
#endif

class GameObject;

class ISteering
{
public:
	virtual Vector2 getForce(GameObject* object) const = 0;
};