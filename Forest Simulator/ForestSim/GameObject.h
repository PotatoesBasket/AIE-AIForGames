#pragma once
#include <vector>
#include <memory>
#include <string>
#include <Renderer2D.h>

#ifndef NDEBUG
#include <Debug/MathLibrary.h>
#else
#include <Release/MathLibrary.h>
#endif

class Component;

class GameObject
{
public:
	GameObject() {}
	virtual ~GameObject() {}

	bool IsActive() const { return m_active; }
	void SetActiveState(bool state) { m_active = state; }

	void update(float deltaTime);
	void updateTransform();
	virtual void onUpdate(float deltaTime) {};

	void draw(std::shared_ptr<aie::Renderer2D> renderer);
	virtual void onDraw(std::shared_ptr<aie::Renderer2D> renderer) {};

	//////////////////////
	// TRANSFORM MATRIX //
	//////////////////////

	const Matrix3& getLocalTransform() const { return m_localTransform; }
	const Matrix3& getGlobalTransform() const { return m_globalTransform; }
	float* getLocalTransformFloat() const { return (float*)& m_localTransform; }
	float* getGlobalTransformFloat() const { return (float*)& m_globalTransform; }

	Vector2 getPosition() { return (Vector2(m_globalTransform.translation.x, m_globalTransform.translation.y)); }

	void setLocalTransform(const Matrix3& m) { m_localTransform = m; }
	void setGlobalTransform(const Matrix3& m) { m_globalTransform = m; }

	void resetTransform();

	void move(float x, float y);
	void move(const Vector2& v);

	void rotate(float degrees);

	void scale(float wMultiplier, float hMultiplier);
	void scale(float multiplier);

	////////////////
	// COMPONENTS //
	////////////////

	void addComponent(const std::shared_ptr<Component>& component);
	void removeComponent(const std::shared_ptr<Component>& component);

	//set all components on/off
	void setComponentsActiveStates(bool state);

	///////////////
	// HIERARCHY //
	///////////////

	GameObject* getParent() const { return m_parent; }
	std::shared_ptr<GameObject> getChild(unsigned int index) const { return m_children[index]; }

	size_t childCount() const { return m_children.size(); }

	void addChild(const std::shared_ptr<GameObject>& child);
	void removeChild(const std::shared_ptr<GameObject>& child);

protected:
	bool m_active = true;

	Matrix3 m_localTransform = Matrix3::identity;
	Matrix3 m_globalTransform = Matrix3::identity;

	std::vector<std::shared_ptr<Component>> m_components;

	GameObject* m_parent = nullptr;
	std::vector<std::shared_ptr<GameObject>> m_children;
};

class Component
{
public:
	virtual ~Component() {}

	virtual void update(GameObject* parent, float deltaTime) {}
	virtual void draw(GameObject* parent, std::shared_ptr<aie::Renderer2D> renderer) {}
	
	bool isActive() const { return m_active; }
	void setActiveState(bool state) { m_active = state; }

protected:
	bool m_active = true;
};