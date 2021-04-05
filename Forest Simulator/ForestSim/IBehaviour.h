#pragma once

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