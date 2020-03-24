#include "NewPathBehaviour.h"
#include "Agent.h"
#include "Graph.h"
#include "Pathfinding.h"

IBehaviour::Result NewPathBehaviour::update(Agent* agent, float deltaTime)
{
	agent->getPath().clear();

	Node* first = agent->getCurrentNode();
	Node* end = agent->getTargetNode();

	if (first == nullptr || end == nullptr)
	{
		agent->getPath().clear();
		return IBehaviour::FAILURE;
	}

	Pathfinding::HeuristicFunc heuristic = Pathfinding::diagonalShortcut;

	if (Pathfinding::findPathAStar(first, end, agent->getPath(), heuristic(first, end)))
	{
		agent->getPath().pop_front();
		return IBehaviour::SUCCESS;
	}

	agent->getPath().clear();
	return IBehaviour::FAILURE;
}