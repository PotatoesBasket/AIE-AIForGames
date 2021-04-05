#include "Pathfinding.h"
#include <stdexcept>
#include <unordered_set>
#include <algorithm>
#include <glm/gtx/norm.hpp>

std::list<Node*> Pathfinding::getPathAStar(Node* startNode, Node* endNode, float heuristic)
{
	//error checks
	if (!startNode || !endNode)
		throw std::runtime_error("Null nodes passed in");

	if (startNode == endNode)
		return std::list<Node*>();

	//initialise starting node
	startNode->runningCost = 0;
	startNode->finalCost = 0;
	startNode->parentNode = nullptr;

	//create temp lists for storing nodes we're visiting/have visited
	std::vector<Node*> openList;
	std::unordered_set<const Node*> closedList;

	//add start node to open list
	openList.push_back(startNode);

	//while open list is not empty
	while (!openList.empty())
	{
		//sort open list by node runningCost + heuristicCost (finalCost)
		auto sortNodes = [](const Node* a, const Node* b) {
			return a->finalCost < b->finalCost; };

		std::sort(openList.begin(), openList.end(), sortNodes);

		//take the node at the top of the list (lowest cost)...
		Node* currentNode = openList.front();

		//exit if we've reached the end of the search
		if (currentNode == endNode)
			break;

		//move current node from open list to closed list
		openList.erase(openList.begin());
		closedList.insert(currentNode);

		//for each of currentNode's connections...
		for (auto& edge : currentNode->outgoingEdges)
		{
			//if destinationNode has not yet been fully processed...
			if (std::find(closedList.begin(), closedList.end(), edge.targetNode) == closedList.end())
			{
				//calculate costs
				float runningCost = currentNode->runningCost + edge.cost;
				float heuristicCost = heuristic;
				float finalCost = runningCost + heuristicCost;

				//if destinationNode has not already been visited...
				if (std::find(openList.begin(), openList.end(), edge.targetNode) == openList.end())
				{
					//update values and add to openList
					edge.targetNode->runningCost = runningCost;
					edge.targetNode->finalCost = finalCost;
					edge.targetNode->parentNode = currentNode;
					openList.push_back(edge.targetNode);
				}
				//otherwise, compare new cost with old cost and overwrite if necessary
				else if (runningCost < edge.targetNode->runningCost)
				{
					edge.targetNode->runningCost = runningCost;
					edge.targetNode->finalCost = finalCost;
					edge.targetNode->parentNode = currentNode;
				}
			}
		}
	}

	//create new list to hold shortest path
	std::list<Node*> path;

	//go backwards from intended destination
	Node* currentNode = endNode;

	//if the destination didn't have a parent, no path was found
	if (!endNode->parentNode)
		return path;

	//create path by iterating through nodes' parents
	while (currentNode)
	{
		path.push_front(currentNode);
		currentNode = currentNode->parentNode;
	}

	return path;
}

bool Pathfinding::findPathAStar(Node* firstNode, Node* secondNode, std::list<Node*>& path, float heuristic)
{
	std::list<Node*> newPath = getPathAStar(firstNode, secondNode, heuristic);

	if (newPath.empty())
		return false;

	path = newPath;
	return true;
}

//good for arbitrarily-placed nodes
float Pathfinding::distanceSqr(Node* firstNode, Node* secondNode)
{
	return glm::length2(secondNode->position - firstNode->position);
}

//good for 4-way grids
float Pathfinding::manhattanDistance(Node* firstNode, Node* secondNode)
{
	return (firstNode->position.x - secondNode->position.x) +
		(firstNode->position.y - secondNode->position.y);
}

//good for 8-way grids (diagonal movement allowed)
float Pathfinding::diagonalShortcut(Node* firstNode, Node* secondNode)
{
	float dx = abs(firstNode->position.x - secondNode->position.x);
	float dy = abs(firstNode->position.y - secondNode->position.y);

	if (dx > dy)
		return (1.4f * dy) + 1.0f * (dx - dy);
	else
		return (1.4f * dx) + 1.0f * (dy - dx);
}