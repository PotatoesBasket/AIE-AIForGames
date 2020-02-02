#pragma once
#include "GameObject.h"
#include "Stat.h"
#include "AnimatedSprite.h"

class Animal : public GameObject
{
public:
	Animal() { reset(); }
	virtual ~Animal() {}

	virtual void onUpdate(float deltaTime) {}
	virtual void onDraw(std::unique_ptr<aie::Renderer2D>) {}

	void reset();
	void spawnNew();

protected:
	Stat m_age;
	Stat m_health;
	Stat m_hunger;
	Stat m_thirst;
	Stat m_energy;

	std::vector<std::unique_ptr<AnimatedSprite>> m_animList;
};