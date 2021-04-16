#pragma once
#include <list>
#include <vector>
#include <glm/vec2.hpp>

struct Node;

struct Edge
{
	Edge(Node* target, float cost = 1.0f) : targetNode(target), cost(cost) {}
	~Edge() {}

	//graph structure
	Node* targetNode = nullptr;

	//pathfinding
	float cost = 1.0f; //cost to travel in this direction
};

struct Node
{
	//graph structure
	std::list<Edge> outgoingEdges;

	//pathfinding
	Node* parentNode = nullptr;
	float runningCost = 0.0f; //current cost to get to this node
	float finalCost = 0.0f; //runningCost + calculated heuristic cost for sorting openList in A* pathfinding

	//custom data
	glm::vec2 position = glm::vec2(0);
};