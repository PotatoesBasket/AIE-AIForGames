#pragma once
#include "AABB.h"

class GameObject;

class Quadtree
{
public:
	Quadtree(const AABB& boundary, unsigned int capacity) : m_boundary(boundary), m_capacity(capacity) {}
	~Quadtree() {}

	bool insert(GameObject* agent);
	void subdivide();
	void query(const AABB& area, std::vector<GameObject*>& foundList);
	void query(const glm::vec2& circleCenter, float circleRadius, std::vector<GameObject*>& foundList);

	void draw(aie::Renderer2D* renderer);

private:
	AABB m_boundary;
	unsigned int m_capacity;
	std::vector<GameObject*> m_agents;
	bool m_divided = false;

	std::unique_ptr<Quadtree> NW = nullptr;
	std::unique_ptr<Quadtree> NE = nullptr;
	std::unique_ptr<Quadtree> SW = nullptr;
	std::unique_ptr<Quadtree> SE = nullptr;
};