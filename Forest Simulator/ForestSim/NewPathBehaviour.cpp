#include "NewPathBehaviour.h"
#include "Agent.h"
#include "Graph.h"
#include "Pathfinding.h"

IBehaviour::Result NewPathBehaviour::update(Agent* agent, float deltaTime)
{
	Node* first = agent->getCurrentNode();
	Node* end = agent->getNearestFood();

	if (first == nullptr || end == nullptr)
		return IBehaviour::SUCCESS;

	Pathfinding::HeuristicFunc heuristic = Pathfinding::diagonalShortcut;

	if (Pathfinding::findPathAStar(first, end, agent->getPath(), heuristic(first, end)))
		return IBehaviour::SUCCESS;

	return IBehaviour::FAILURE;
}