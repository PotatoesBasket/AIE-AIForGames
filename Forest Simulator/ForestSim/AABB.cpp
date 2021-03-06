#include "AABB.h"

AABB::AABB(const glm::vec2& min, const glm::vec2& max) :
	m_min(min),
	m_max(max),
	m_width(max.x - min.x),
	m_height(max.y - min.y) {}

AABB::AABB(const glm::vec2& center, float width, float height) :
	m_min(glm::vec2(center.x - width * 0.5f, center.y - height * 0.5f)),
	m_max(glm::vec2(center.x + width * 0.5f, center.y + height * 0.5f)),
	m_width(width),
	m_height(height) {}

/*Returns the position of the bounding box's centre.*/
glm::vec2 AABB::center() const
{
	return (m_min + m_max) * 0.5f;
}

glm::vec2 AABB::closestPoint(const glm::vec2& point) const
{
	return clamp(point, m_min, m_max);
}

/*Returns true if bounding box is encompassing a given point.*/
bool AABB::containsPoint(const glm::vec2& point) const
{
	//if any of these are false, there is no overlap
	return !(point.x < m_min.x || point.y < m_min.y ||
		point.x >= m_max.x || point.y >= m_max.y);
}

/*Returns true if bounding box is overlapping with another box.*/
bool AABB::overlapsAABB(const AABB& box) const
{
	return !(m_max.x < box.m_min.x || m_max.y < box.m_min.y ||
		m_min.x > box.m_max.x || m_min.y > box.m_max.y);
}

bool AABB::overlapsCircle(const glm::vec2& circleCenter, float circleRadius) const
{
	glm::vec2 diff = closestPoint(circleCenter) - circleCenter;
	return glm::length(diff) < circleRadius;
}

void AABB::update(GameObject* gameObject, float deltaTime)
{
	m_min.x = gameObject->getLocalTransform()[2][0] - width() * 0.5f;
	m_min.y = gameObject->getLocalTransform()[2][1] - height() * 0.5f;
	m_max.x = gameObject->getLocalTransform()[2][0] + width() * 0.5f;
	m_max.y = gameObject->getLocalTransform()[2][1] + height() * 0.5f;
}

void AABB::draw(aie::Renderer2D* renderer)
{
	//DEBUG
	renderer->setRenderColour(0, 0, 1, 1);
	renderer->drawLine(m_min.x, m_min.y, m_max.x, m_min.y, 1, 0); //bottom
	renderer->drawLine(m_max.x, m_min.y, m_max.x, m_max.y, 1, 0); //right
	renderer->drawLine(m_max.x, m_max.y, m_min.x, m_max.y, 1, 0); //top
	renderer->drawLine(m_min.x, m_max.y, m_min.x, m_min.y, 1, 0); //left
	renderer->setRenderColour(1, 1, 1, 1);
	//DEBUG
}

float AABB::clamp(float t, float a, float b) const
{
	return max(a, min(b, t));
}

glm::vec2 AABB::clamp(const glm::vec2& t, const glm::vec2& a, const glm::vec2& b) const
{
	return max(a, min(b, t));
}