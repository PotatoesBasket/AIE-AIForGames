#pragma once
#include "Agent.h"

class AgentPool
{
public:
	AgentPool(std::vector<Agent*> agents) { m_agentList = agents; }
	~AgentPool();

	bool activateNext(glm::vec2 position, int state = 0); // 0 for fresh stats, 1 for random
	std::vector<Agent*>& getAgentList() { return m_agentList; }

	void update(float deltaTime);
	void draw(std::shared_ptr<aie::Renderer2D> renderer);

private:
	std::vector<Agent*> m_agentList;
};