#include "InverseDecorator.h"

IBehaviour::Result InverseDecorator::update(Agent* agent, float deltaTime)
{
	Result result = m_child->update(agent, deltaTime);

	switch (result)
	{
	case IBehaviour::FAILURE:
		return SUCCESS;

	case IBehaviour::SUCCESS:
		return FAILURE;

	default:
		return INVALID;
	}
}