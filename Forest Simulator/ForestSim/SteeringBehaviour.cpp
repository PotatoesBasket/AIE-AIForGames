#include "SteeringBehaviour.h"
#include "GameObject.h"

IBehaviour::Result SteeringBehaviour::update(GameObject* object, float deltaTime)
{
	for (auto& force : m_steeringForces)
		object->addForce(force->getForce(object));

	return ONGOING;
}