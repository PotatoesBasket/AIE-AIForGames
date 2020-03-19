#pragma once
#ifndef NDEBUG
#include <Debug/MathLibrary.h>
#else
#include <Release/MathLibrary.h>
#endif

class Agent;

//Base class for all behaviours

class IBehaviour
{
public:
	enum Result
	{
		INVALID,
		FAILURE,
		SUCCESS,
		ONGOING
	};

	virtual Result update(Agent* agent, float deltaTime) = 0;

protected:
	Result m_result = INVALID;
};