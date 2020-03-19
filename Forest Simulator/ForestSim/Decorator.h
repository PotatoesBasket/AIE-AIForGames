#pragma once
#include "IBehaviour.h"
#include <memory>

class Decorator : public IBehaviour
{
public:
	virtual Result update(Agent* agent, float deltaTime) = 0;

	void setChild(std::shared_ptr<IBehaviour> child) { m_child = child; }

protected:
	std::shared_ptr<IBehaviour> m_child;
};