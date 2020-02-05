#pragma once
#ifndef NDEBUG
#include <Debug/MathLibrary.h>
#else
#include <Release/MathLibrary.h>
#endif

class GameObject;

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

	virtual Result update(GameObject* object, float deltaTime) = 0;

protected:
	Result m_result = INVALID;
};