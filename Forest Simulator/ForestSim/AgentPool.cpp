#include "AgentPool.h"
#include "Bunny.h"
#include "Fox.h"

AgentPool::~AgentPool()
{
	for (auto& agent : m_agentList)
		delete agent;
}

/*Looks for the first inactive agent in agent list and activates it.*/
// state determines whether stats are reset or not
bool AgentPool::activateNext(Vector2 position, int state)
{
	std::vector<Agent*>::iterator it = m_agentList.begin();

	for (; it != m_agentList.end(); ++it)
	{
		if ((*it)->isActive() == false)
		{
			(*it)->setPosition(position);
			state == 0 ? (*it)->getStats()->reset() : 0;
			(*it)->setActiveState(true);
			return true;
		}
	}

	return false;
}

/*Calls update on all agents in pool.*/
void AgentPool::update(float deltaTime)
{
	for (auto agent : m_agentList)
		agent->update(deltaTime);
}

/*Calls draw on all agents in pool.*/
void AgentPool::draw(std::shared_ptr<aie::Renderer2D> renderer)
{
	for (auto agent : m_agentList)
		agent->draw(renderer);
}