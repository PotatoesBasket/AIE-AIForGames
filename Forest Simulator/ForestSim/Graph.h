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
	Edge() {}
	Edge(Node* target, float cost) : destinationNode(target), cost(cost) {}
	~Edge() {}

	//graph structure
	Node* destinationNode = nullptr;

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
	Vector2 position = Vector2{ 0, 0 };
};

struct NavMeshNode : public Node
{
	//edges
	std::vector<Vector2> vertices;

	//gets the number of shared verts
	int getAdjacentVertices(NavMeshNode* other, Vector2* adjacent)
	{
		int count = 0;

		for (auto v : vertices)
		{
			for (auto v2 : other->vertices)
			{
				if (v.x == v2.x &&
					v.y == v2.y)
				{
					adjacent[count++] = v;
					break;
				}
			}
		}

		return count;
	}
};