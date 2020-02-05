#include "Composite.h"

IBehaviour::Result Composite::update(GameObject* object, float deltaTime)
{
	while (true)
	{
		Result result = (*m_currentChild)->update(object, deltaTime);

		if (result != m_endOfArrayResult)
			return result;

		//Iterate to next child
		//If end of array was hit, behaviour either failed (selector) or succeeded (sequence)
		if (++m_currentChild == m_children.end())
			return m_endOfArrayResult;
	}
}

void Composite::addBehaviour(std::shared_ptr<IBehaviour> behaviour)
{
	m_children.push_back(behaviour);
	m_currentChild = m_children.begin();
}