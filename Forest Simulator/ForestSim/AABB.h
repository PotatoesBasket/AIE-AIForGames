#pragma once
#include "GameObject.h"
#include <Renderer2D.h>

class AABB
{
public:
	AABB(const glm::vec2& min, const glm::vec2& max) : m_min(min), m_max(max),
		m_width(max.x - min.x), m_height(max.y - min.y) {}
	~AABB() {}

	glm::vec2 center() const;
	float width() const { return m_width; }
	float height() const { return m_height; }
	glm::vec2 closestPoint(const glm::vec2& point) const;

	bool isInsideBox(const glm::vec2& point) const;
	bool overlaps(const AABB& other) const;

	void update(GameObject* gameObject, float deltaTime); //update position
	void draw(std::shared_ptr<aie::Renderer2D> renderer); //debug only

	float min(float a, float b) const { return a < b ? a : b; }
	float max(float a, float b) const { return a > b ? a : b; }
	glm::vec2 min(const glm::vec2& a, const glm::vec2& b) const { return { min(a.x, b.x), min(a.y, b.y) }; }
	glm::vec2 max(const glm::vec2& a, const glm::vec2& b) const { return { max(a.x, b.x), max(a.y, b.y) }; }
	float clamp(float t, float a, float b) const;
	glm::vec2 clamp(const glm::vec2& t, const glm::vec2& a, const glm::vec2& b) const;

private:
	glm::vec2 m_min;
	glm::vec2 m_max;
	float m_width;
	float m_height;
};