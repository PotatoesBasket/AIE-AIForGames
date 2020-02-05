#pragma once
#include "Graph.h"
#include <functional>

class Pathfinding
{
public:
	//don't set a heuristic to do a Dijkstra search
	static std::list<Node*> getPathAStar(Node* startNode, Node* endNode, float heuristic = 0);
	static bool findPathAStar(Node* startNode, Node* endNode, std::list<Node*>& path, float heuristic = 0);

	//heuristic functions
	typedef std::function<float(Node* firstNode, Node* secondNode)> HeuristicFunc;
	static float distanceSqr(Node* firstNode, Node* secondNode);
	static float manhattanDistance(Node* firstNode, Node* secondNode);
	static float diagonalShortcut(Node* firstNode, Node* secondNode);
};