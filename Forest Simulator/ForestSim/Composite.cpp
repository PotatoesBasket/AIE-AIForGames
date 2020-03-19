#include "Composite.h"

IBehaviour::Result Composite::update(Agent* agent, float deltaTime)
{
	while (true)
	{
		if (m_currentChild == m_children.end())
		{
			m_currentChild = m_children.begin();
			return m_endOfArrayResult;
		}

		Result result = (*m_currentChild)->update(agent, deltaTime);

		if (result != m_endOfArrayResult)
		{
			m_currentChild = m_children.begin();
			return result;
		}

		//Iterate to next child
		//If end of array was hit, behaviour either failed (selector) or succeeded (sequence)
		if (++m_currentChild == m_children.end())
		{
			m_currentChild = m_children.begin();
			return m_endOfArrayResult;
		}
	}
}

void Composite::addBehaviour(std::shared_ptr<IBehaviour> behaviour)
{
	m_children.push_back(behaviour);
	m_currentChild = m_children.begin();
}