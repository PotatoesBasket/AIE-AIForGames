#include "AABB.h"

/*Returns the position of the bounding box's centre.*/
Vector2 AABB::center() const
{
	return (m_min + m_max) * 0.5f;
}

Vector2 AABB::closestPoint(const Vector2& point) const
{
	return clamp(point, m_min, m_max);
}

/*Returns true if bounding box is encompassing a given point.*/
bool AABB::isInsideBox(const Vector2& point) const
{
	//if any of these are false, there is no overlap
	return !(point.x < m_min.x || point.y < m_min.y ||
		point.x > m_max.x || point.y > m_max.y);
}

/*Returns true if bounding box is overlapping with another box.*/
bool AABB::overlaps(const AABB& box) const
{
	return !(m_max.x < box.m_min.x || m_max.y < box.m_min.y ||
		m_min.x > box.m_max.x || m_min.y > box.m_max.y);
}

void AABB::update(GameObject* gameObject, float deltaTime)
{
	m_min.x = gameObject->getLocalTransform().translation.x - width() * 0.5f;
	m_min.y = gameObject->getLocalTransform().translation.y - height() * 0.5f;
	m_max.x = gameObject->getLocalTransform().translation.x + width() * 0.5f;
	m_max.y = gameObject->getLocalTransform().translation.y + height() * 0.5f;
}

void AABB::draw(std::shared_ptr<aie::Renderer2D> renderer)
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

Vector2 AABB::clamp(const Vector2& t, const Vector2& a, const Vector2& b) const
{
	return max(a, min(b, t));
}