#pragma once
#include "GameObject.h"
#include <Renderer2D.h>

class AABB
{
public:
	AABB(const Vector2& min, const Vector2& max) : m_min(min), m_max(max),
		m_width(max.x - min.x), m_height(max.y - min.y) {}
	~AABB() {}

	Vector2 center() const;
	float width() const { return m_width; }
	float height() const { return m_height; }
	Vector2 closestPoint(const Vector2& point) const;

	bool isInsideBox(const Vector2& point) const;
	bool overlaps(const AABB& other) const;

	void update(GameObject* gameObject, float deltaTime); //update position
	void draw(std::shared_ptr<aie::Renderer2D> renderer); //debug only

	float min(float a, float b) const { return a < b ? a : b; }
	float max(float a, float b) const { return a > b ? a : b; }
	Vector2 min(const Vector2& a, const Vector2& b) const { return { min(a.x, b.x), min(a.y, b.y) }; }
	Vector2 max(const Vector2& a, const Vector2& b) const { return { max(a.x, b.x), max(a.y, b.y) }; }
	float clamp(float t, float a, float b) const;
	Vector2 clamp(const Vector2& t, const Vector2& a, const Vector2& b) const;

private:
	Vector2 m_min;
	Vector2 m_max;
	float m_width;
	float m_height;
};