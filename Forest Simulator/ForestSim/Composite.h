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

	void addBehaviour(std::shared_ptr<IBehaviour> behaviour);
	void reset() { m_currentChild = m_children.begin(); }

protected:
	Result m_endOfArrayResult = INVALID;
	std::vector<std::shared_ptr<IBehaviour>> m_children;
	std::vector<std::shared_ptr<IBehaviour>>::iterator m_currentChild = m_children.begin();
};