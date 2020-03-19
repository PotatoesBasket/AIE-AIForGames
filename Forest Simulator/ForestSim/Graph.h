#pragma once
#include <list>
#include <vector>

#ifndef NDEBUG
#include <Debug/MathLibrary.h>
#else
#include <Release/MathLibrary.h>
#endif

struct Node;

struct Edge
{
	Edge(Node* target, float cost = 1) : targetNode(target), cost(cost) {}
	~Edge() {}

	//graph structure
	Node* targetNode = nullptr;

	//pathfinding
	float cost = 1; //cost to travel in this direction
};

struct Node
{
	//graph structure
	std::list<Edge> outgoingEdges;

	//pathfinding
	Node* parentNode = nullptr;
	float runningCost = 0; //current cost to get to this node
	float finalCost = 0; //runningCost + calculated heuristic cost for sorting openList in A* pathfinding

	//custom data
	Vector2 position;
};