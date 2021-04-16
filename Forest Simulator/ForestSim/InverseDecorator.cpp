#include "InverseDecorator.h"

IBehaviour::Result InverseDecorator::update(Agent* agent, float deltaTime)
{
	Result result = m_child->update(agent, deltaTime);

	switch (result)
	{
	case IBehaviour::Result::FAILURE:
		return Result::SUCCESS;

	case IBehaviour::Result::SUCCESS:
		return Result::FAILURE;

	default:
		return Result::INVALID;
	}
}