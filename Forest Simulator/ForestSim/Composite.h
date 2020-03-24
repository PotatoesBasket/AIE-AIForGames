#pragma once
#include "IBehaviour.h"
#include <vector>
#include <memory>

class Agent;

//Base class for sequence and selector nodes
class Composite : public IBehaviour
{
public:
	Result update(Agent* agent, float deltaTime) override;

	void addBehaviour(IBehaviour* behaviour);
	void reset() { m_currentChild = m_children.begin(); }

protected:
	Result m_continueResult = INVALID;
	std::vector<IBehaviour*> m_children;
	std::vector<IBehaviour*>::iterator m_currentChild = m_children.begin();
};