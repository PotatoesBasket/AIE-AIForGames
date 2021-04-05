#pragma once
#include "GameObject.h"
#include "Graph.h"

class Sprite;

class Tile : public Node
{
public:
	enum Type
	{
		ground,
		water,
		tree,
		grass
	};
	
	Tile(Type type, glm::vec2 position) : m_type(type) { this->position = position; }
	~Tile() {}

	void addEdge(Node* target, float cost = 1) { outgoingEdges.push_back(Edge(target, cost)); }

	glm::vec2 const getPosition() { return position; }
	Type const getType() { return m_type; }

private:
	Type m_type;
};