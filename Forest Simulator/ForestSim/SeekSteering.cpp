#include "SeekSteering.h"
#include "GameObject.h"

Vector2 SeekSteering::getForce(GameObject* object) const
{
	Vector2 force = Vector2(0, 0);

	if (!m_target)
		return force;

	Vector2 velocity =
		(m_target->getPosition() - object->getPosition()).normalised() * m_speed;

	force = velocity - object->getVelocity();

	return force;
}