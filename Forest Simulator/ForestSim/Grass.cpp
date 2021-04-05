#include "Grass.h"
#include "Sprite.h"
#include "RNG.h"

Grass::Grass(glm::vec2 position)
{
	setPosition(position);

	// create and attach sprite components
	m_lowGrass = std::make_shared<Sprite>(grassLow);
	m_highGrass = std::make_shared<Sprite>(grassHigh);

	addComponent(m_lowGrass);
	addComponent(m_highGrass);

	// start growth at random level
	RNG& rng = RNG::getInstance();

	rng.setIntRange(0, m_maxHP);
	m_hp = rng.nextInt();

	rng.setFloatRange(0, m_growthRate);
	m_timer = rng.nextFloat();

	// set starting sprite
	updateSprite();
}

void Grass::onUpdate(float deltaTime)
{
	// grass growth
	if (m_hp < m_maxHP)
	{
		m_timer += deltaTime;

		if (m_timer >= m_growthRate)
		{
			++m_hp;
			m_timer = 0;
			updateSprite();
		}
	}
}

// Get ate
void Grass::reduceHP()
{
	if (m_hp > 0)
	{
		--m_hp;
		updateSprite();
	}
}

// Set current sprite based on hp
void Grass::updateSprite()
{
	if (m_hp == 0)
	{
		m_lowGrass->setActiveState(false);
		m_highGrass->setActiveState(false);
	}
	else if (m_hp < m_maxHP)
	{
		m_lowGrass->setActiveState(true);
		m_highGrass->setActiveState(false);
	}
	else
	{
		m_lowGrass->setActiveState(false);
		m_highGrass->setActiveState(true);
	}
}