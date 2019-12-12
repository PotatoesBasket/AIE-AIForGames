#include "GameObject.h"

GameObject::~GameObject()
{
	if (m_parent) //if object has a parent...
		m_parent->removeChild(this); //remove object from parent's list of children

	for (auto& child : m_children) //for all object's children...
		child->m_parent = nullptr; //remove object from all childrens' parent pointers
}

void GameObject::setActiveState(bool state)
{
	m_active = state;

	if (m_active == true)
	{
		allComponentsOn();
	}
	else
	{
		allComponentsOff();
	}
}

//////////////////////////////
//   Updating and Drawing   //
//////////////////////////////

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

/*Updates the object's transform taking the parent's transform into account,
then does the same for its children.*/
void GameObject::updateTransform()
{
	if (m_parent != nullptr)
		m_globalTransform = m_parent->m_globalTransform * m_localTransform;
	else
		m_globalTransform = m_localTransform;

	for (auto child : m_children)
		child->updateTransform();
}

/*If object is alive, draw the object itself, then its components (if active), then its children.*/
void GameObject::draw(aie::Renderer2D* renderer)
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

///////////////////
//   Transform   //
///////////////////

void GameObject::setLocalTransform(const Matrix3& m)
{
	m_localTransform = m;
}

void GameObject::setGlobalTransform(const Matrix3& m)
{
	m_globalTransform = m;
}

void GameObject::resetTransform()
{
	m_localTransform = Matrix3::identity;
	m_globalTransform = Matrix3::identity;
	m_rotation = 0;
}

Vector2 GameObject::getPosition()
{
	return (Vector2(m_globalTransform.translation.x, m_globalTransform.translation.y));
}

void GameObject::move(float x, float y)
{
	m_localTransform.translate(x, y);
	updateTransform();
}
void GameObject::move(const Vector2& v)
{
	m_localTransform.translate(v);
	updateTransform();
}

void GameObject::moveForward(float speed)
{
	float x = -sinf(m_rotation * 3.1415926f / 180) * speed;
	float y = cosf(m_rotation * 3.1415926f / 180) * speed;

	move(x, y);
}

void GameObject::rotate(float degrees)
{
	m_rotation += degrees;
	m_localTransform.rotateZDegrees(degrees);
	updateTransform();
}

void GameObject::scale(float wMultiplier, float hMultiplier)
{
	m_localTransform.scale(wMultiplier, hMultiplier, 1);
	updateTransform();
}
void GameObject::scale(float multiplier)
{
	m_localTransform.scale(Vector3(multiplier, multiplier, 1));
	updateTransform();
}

///////////////////
//   Hierarchy   //
///////////////////

void GameObject::addChild(GameObject* child)
{
	if (!child->m_parent) //make sure object isn't already parented to something
	{
		child->m_parent = this; //assign parent to child
		m_children.push_back(child); //add child to parent's list of children
	}
}

void GameObject::removeChild(GameObject* child)
{
	auto it = std::find(m_children.begin(), m_children.end(), child); //find child in list

	if (it != m_children.end())
	{
		m_children.erase(it); //remove child from list
		child->m_parent = nullptr; //remove parent from child
	}
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

void GameObject::allComponentsOn()
{
	for (auto& component : m_components)
		component->setActiveState(true);
}

void GameObject::allComponentsOff()
{
	for (auto& component : m_components)
		component->setActiveState(false);
}