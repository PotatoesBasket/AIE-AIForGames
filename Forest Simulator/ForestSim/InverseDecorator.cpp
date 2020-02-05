#include "InverseDecorator.h"

IBehaviour::Result InverseDecorator::update(GameObject* object, float deltaTime)
{
	Result result = m_child->update(object, deltaTime);

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