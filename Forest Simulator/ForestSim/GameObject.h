#pragma once
#include <vector>
#include <memory>
#include <string>
#include <Renderer2D.h>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

class Component;

class GameObject
{
public:
	GameObject() {}
	virtual ~GameObject() {}

	bool isActive() const { return m_active; }
	void setActiveState(bool state) { m_active = state; }

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);

	virtual void onUpdate(float deltaTime) {};
	virtual void onDraw(aie::Renderer2D* renderer) {};

private:
	void updateTransform();

public:
	//////////////////////
	// TRANSFORM MATRIX //
	//////////////////////

	const glm::mat3& getLocalTransform() const { return m_localTransform; }
	const glm::mat3& getGlobalTransform() const { return m_globalTransform; }
	float* getLocalTransformFloat() const { return (float*)& m_localTransform; }
	float* getGlobalTransformFloat() const { return (float*)& m_globalTransform; }

	void setLocalTransform(const glm::mat3& m) { m_localTransform = m; }
	void setGlobalTransform(const glm::mat3& m) { m_globalTransform = m; }

	void setPosition(glm::vec2 position) { m_globalTransform = glm::translate(glm::mat3(1.0f), position); }
	glm::vec2 getPosition() const { return (glm::vec2(m_globalTransform[2][0], m_globalTransform[2][1])); }

	void move(float x, float y);
	void move(const glm::vec2& v);

	void rotate(float degrees);

	void scale(float wMultiplier, float hMultiplier);
	void scale(float multiplier);

	void resetTransform();

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

	glm::mat3 m_localTransform = glm::mat3(1.0f);
	glm::mat3 m_globalTransform = glm::mat3(1.0f);

	std::vector<std::shared_ptr<Component>> m_components;

	GameObject* m_parent = nullptr;
	std::vector<std::shared_ptr<GameObject>> m_children;
};

class Component
{
public:
	virtual ~Component() {}

	virtual void update(GameObject* parent, float deltaTime) {}
	virtual void draw(GameObject* parent, aie::Renderer2D* renderer) {}
	
	bool isActive() const { return m_active; }
	void setActiveState(bool state) { m_active = state; }

protected:
	bool m_active = true;
};