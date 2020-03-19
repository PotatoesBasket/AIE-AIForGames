#pragma once
#include "IBehaviour.h"

class Agent;
class Node;

// finds a path from Agent's position to target using A*
class NewPathBehaviour : public IBehaviour
{
public:
	NewPathBehaviour(Node* target) : m_target(target) {}
	~NewPathBehaviour() {}

	Result update(Agent* agent, float deltaTime) override;

private:
	Node* m_target;
};