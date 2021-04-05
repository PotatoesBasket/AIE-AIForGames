#include "GameObject.h"

/*If object is alive, update the object itself, then its components (if active), then its children.*/
void GameObject::update(float deltaTime)
{
	if (m_active)
	{
		onUpdate(deltaTime);

		for (auto component : m_components)
			if (component->isActive())
				component->update(this, deltaTime);

		for (auto child : m_children)
			child->update(deltaTime);
	}
}

/*If object is alive, draw the object itself, then its components (if active), then its children.*/
void GameObject::draw(std::shared_ptr<aie::Renderer2D> renderer)
{
	if (m_active)
	{
		onDraw(renderer);

		for (auto component : m_components)
			if (component->isActive())
				component->draw(this, renderer);

		for (auto child : m_children)
			child->draw(renderer);
	}
}

/*Updates the object's transform taking the parent's transform into account,
then does the same for its children.*/
void GameObject::updateTransform()
{
	if (m_parent)
		m_globalTransform = m_parent->m_globalTransform * m_localTransform;
	else
		m_globalTransform = m_localTransform;

	for (auto child : m_children)
		child->updateTransform();
}

///////////////////
//   Transform   //
///////////////////

void GameObject::move(float x, float y)
{
	m_localTransform = glm::translate(m_localTransform, glm::vec2(x, y));
	updateTransform();
}
void GameObject::move(const glm::vec2& v)
{
	m_localTransform = glm::translate(m_localTransform, v);
	updateTransform();
}

void GameObject::rotate(float radians)
{
	m_localTransform = glm::rotate(m_localTransform, radians);
	updateTransform();
}

void GameObject::scale(float wMultiplier, float hMultiplier)
{
	m_localTransform = glm::scale(m_localTransform, glm::vec2(wMultiplier, hMultiplier));
	updateTransform();
}
void GameObject::scale(float multiplier)
{
	m_localTransform = glm::scale(m_localTransform, glm::vec2(multiplier, multiplier));
	updateTransform();
}

void GameObject::resetTransform()
{
	m_localTransform = glm::mat3(1.0f);
	m_globalTransform = glm::mat3(1.0f);
}


/////////////////////
//   Components   ///
/////////////////////

void GameObject::addComponent(const std::shared_ptr<Component>& component)
{
	m_components.push_back(component);
}

void GameObject::removeComponent(const std::shared_ptr<Component>& component)
{
	auto it = std::find(m_components.begin(), m_components.end(), component);

	if (it != m_components.end())
		m_components.erase(it);
}

void GameObject::setComponentsActiveStates(bool state)
{
	for (auto& component : m_components)
		component->setActiveState(state);
}

///////////////////
//   Hierarchy   //
///////////////////

void GameObject::addChild(const std::shared_ptr<GameObject>& child)
{
	if (!child->m_parent) //make sure object isn't already parented to something
	{
		child->m_parent = this; //assign parent to child
		m_children.push_back(child); //add child to parent's list of children
	}
}

void GameObject::removeChild(const std::shared_ptr<GameObject>& child)
{
	auto it = std::find(m_children.begin(), m_children.end(), child); //find child in list

	if (it != m_children.end())
	{
		m_children.erase(it); //remove child from list
		child->m_parent = nullptr; //remove parent from child
	}
}