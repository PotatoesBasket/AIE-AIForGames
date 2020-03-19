#pragma once
#ifndef NDEBUG
#include <Debug/MathLibrary.h>
#else
#include <Release/MathLibrary.h>
#endif

class Agent;

//Base for all steering forces

class ISteering
{
public:
	virtual Vector2 getForce(Agent* agent) const = 0;
};