#include "Agent.h"
#include "IBehaviour.h"
#include "Map.h"

void Agent::update(float deltaTime)
{
	if (m_active)
	{
		onUpdate(deltaTime);

		m_bhTimer += deltaTime;
		updateBehaviours();

		//clamp velocity
		if (m_velocity.magnitudeSqr() > m_maxVelocity * m_maxVelocity)
			m_velocity = m_velocity.normalised() * m_maxVelocity;

		//update position
		setPosition(getPosition() + m_velocity * deltaTime);

		//update components
		for (auto component : m_components)
			if (component->isActive())
				component->update(this, deltaTime);

		//update children
		for (auto child : m_children)
			child->update(deltaTime);
	}
}

Node* Agent::getCurrentNode()
{
	return m_currentMap->getNodeAtPosition(getPosition().x, getPosition().y);
}

Node* Agent::getNearestWater()
{
	Node* closestWater = nullptr;

	return closestWater;
}

void Agent::updateBehaviours()
{
	//behaviours don't need to be updated every frame
	if (m_bhTimer > m_bhDelay)
	{
		for (auto& behaviour : m_behaviourList)
			behaviour->update(this, m_bhDelay); // cap deltaTime at delay rate

		m_bhTimer = 0;
	}
}