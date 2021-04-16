#include "Quadtree.h"
#include "GameObject.h"

bool Quadtree::insert(GameObject* agent)
{
	if (!m_boundary.containsPoint(agent->getPosition()))
		return false;

	if (m_agents.size() < m_capacity)
	{
		m_agents.push_back(agent);
		return true;
	}
	else
	{
		if (!m_divided)
			subdivide();

		if (NW->insert(agent))
			return true;

		if (NE->insert(agent))
			return true;

		if (SW->insert(agent))
			return true;

		if (SE->insert(agent))
			return true;
	}
}

void Quadtree::subdivide()
{
	AABB nw = AABB(
		glm::vec2(m_boundary.center().x - m_boundary.width() * 0.25f,
			m_boundary.center().y + m_boundary.height() * 0.25f),
		m_boundary.width() * 0.5f,
		m_boundary.height() * 0.5f);

	AABB ne = AABB(
		glm::vec2(m_boundary.center().x + m_boundary.width() * 0.25f,
			m_boundary.center().y + m_boundary.height() * 0.25f),
		m_boundary.width() * 0.5f,
		m_boundary.height() * 0.5f);

	AABB sw = AABB(
		glm::vec2(m_boundary.center().x - m_boundary.width() * 0.25f,
			m_boundary.center().y - m_boundary.height() * 0.25f),
		m_boundary.width() * 0.5f,
		m_boundary.height() * 0.5f);

	AABB se = AABB(
		glm::vec2(m_boundary.center().x + m_boundary.width() * 0.25f,
			m_boundary.center().y - m_boundary.height() * 0.25f),
		m_boundary.width() * 0.5f,
		m_boundary.height() * 0.5f);

	NE = std::make_unique<Quadtree>(nw, m_capacity);
	NW = std::make_unique<Quadtree>(ne, m_capacity);
	SE = std::make_unique<Quadtree>(sw, m_capacity);
	SW = std::make_unique<Quadtree>(se, m_capacity);

	m_divided = true;
}

void Quadtree::query(const AABB& area, std::vector<GameObject*>& foundList)
{
	if (!m_boundary.overlapsAABB(area))
		return;
	else
	{
		for (auto& p : m_agents)
		{
			if (area.containsPoint(p->getPosition()))
				foundList.push_back(p);
		}

		if (m_divided)
		{
			NW->query(area, foundList);
			NE->query(area, foundList);
			SW->query(area, foundList);
			SE->query(area, foundList);
		}
	}
}

void Quadtree::query(const glm::vec2& circleCenter, float circleRadius, std::vector<GameObject*>& foundList)
{
	if (!m_boundary.overlapsCircle(circleCenter, circleRadius))
		return;
	else
	{
		for (auto& p : m_agents)
		{
			if (glm::length(circleCenter - p->getPosition()) < circleRadius)
				foundList.push_back(p);
		}

		if (m_divided)
		{
			NW->query(circleCenter, circleRadius, foundList);
			NE->query(circleCenter, circleRadius, foundList);
			SW->query(circleCenter, circleRadius, foundList);
			SE->query(circleCenter, circleRadius, foundList);
		}
	}
}

void Quadtree::draw(aie::Renderer2D* renderer)
{
	//ew
	glm::vec2 min = glm::vec2(m_boundary.center().x - m_boundary.width() * 0.5f, m_boundary.center().y - m_boundary.height() * 0.5f);
	glm::vec2 max = glm::vec2(m_boundary.center().x + m_boundary.width() * 0.5f, m_boundary.center().y + m_boundary.height() * 0.5f);

	renderer->setRenderColour(0.0f, 0.0f, 0.0f, 1.0f);
	renderer->drawLine(min.x, min.y, max.x, min.y, 3, 0); //bottom
	renderer->drawLine(max.x, min.y, max.x, max.y, 3, 0); //right
	renderer->drawLine(max.x, max.y, min.x, max.y, 3, 0); //top
	renderer->drawLine(min.x, max.y, min.x, min.y, 3, 0); //left

	if (m_divided)
	{
		NW->draw(renderer);
		NE->draw(renderer);
		SW->draw(renderer);
		SE->draw(renderer);
	}
}