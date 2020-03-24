#include "Composite.h"

IBehaviour::Result Composite::update(Agent* agent, float deltaTime)
{
	while (true)
	{
		// execute current behaviour
		Result result = (*m_currentChild)->update(agent, deltaTime);

		// if result was ongoing, composite needed to reset
		// while still completing parent composite requisite
		if (result == Result::ONGOING)
		{
			m_currentChild = m_children.begin();
			return m_continueResult;
		}

		// if sequence failed or selector succeeded
		// reset and return result
		if (result != m_continueResult)
		{
			m_currentChild = m_children.begin();
			return result;
		}

		// iterate to next child
		// check if end of array reached
		if (++m_currentChild == m_children.end())
		{
			m_currentChild = m_children.begin();
			return m_continueResult;
		}
	}
}

void Composite::addBehaviour(IBehaviour* behaviour)
{
	m_children.push_back(behaviour);
	m_currentChild = m_children.begin();
}