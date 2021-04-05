#pragma once
#include "GameObject.h"

class Sprite;

class Grass : public GameObject
{
public:
	Grass(glm::vec2 position);
	~Grass() {}

	void onUpdate(float deltaTime) override;

	bool isEdible() const { return m_hp > 0; }
	void reduceHP();

private:
	void updateSprite();

private:
	int m_hp = 0;
	const int m_maxHP = 3;

	float m_timer = 0;
	const float m_growthRate = 30;

	std::shared_ptr<Sprite> m_lowGrass;
	std::shared_ptr<Sprite> m_highGrass;
};