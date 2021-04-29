#include "NewPathBehaviour.h"
#include "Agent.h"
#include "Graph.h"
#include "Pathfinding.h"
#include <chrono>
#include "DebugManager.h"

IBehaviour::Result NewPathBehaviour::update(Agent* agent, float deltaTime)
{
	//
	auto t1 = std::chrono::high_resolution_clock::now();
	//

	agent->getPath().clear();

	Node* first = agent->getCurrentNode();
	Node* end = agent->m_targetNode;

	if (first == nullptr || end == nullptr)
	{
		agent->getPath().clear();
		return IBehaviour::Result::FAILURE;
	}

	Pathfinding::HeuristicFunc heuristic = Pathfinding::diagonalShortcut;

	if (Pathfinding::findPathAStar(first, end, agent->getPath(), heuristic(first, end)))
	{
		agent->getPath().pop_front();

		//
		auto t2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> t = t2 - t1;
		DebugManager::current().totalFuncTimePathing += t.count();
		DebugManager::current().noOfFindingNewPath++;
		//

		return IBehaviour::Result::SUCCESS;
	}

	agent->getPath().clear();
	return IBehaviour::Result::FAILURE;
}