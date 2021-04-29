#include "Life.h"
#include "RNG.h"

void Stat::update(float deltaTime)
{
	m_timer += deltaTime;

	if (m_timer >= 1.0f)
	{
		currentPercent += m_inc;
		m_timer = 0.0f;
	}
}

Life::Life(float ageRate, float hungerRate, float energyRate)
{
	m_age = std::make_unique<Stat>(ageRate);
	m_hunger = std::make_unique<Stat>(hungerRate);
	m_energy = std::make_unique<Stat>(energyRate);

	RNG& rng = RNG::getInstance();
	rng.setFloatRange(0.0f, 0.5f);

	m_age->currentPercent = rng.nextFloat();
	m_hunger->currentPercent = rng.nextFloat();
	m_energy->currentPercent = rng.nextFloat();
}

void Life::update(GameObject* parent, float deltaTime)
{
	m_age->update(deltaTime);
	m_hunger->update(deltaTime);
	m_energy->update(deltaTime);

	// kill object if a stat gets maxed
	if (m_age->currentPercent >= 1.0f ||
		m_hunger->currentPercent >= 1.0f ||
		m_energy->currentPercent >= 1.0f)
		parent->setActiveState(false);
}

void Life::draw(GameObject* parent, aie::Renderer2D* renderer)
{
	// draw stat sliders above parent in grey
	renderer->setRenderColour(0.5f, 0.5f, 0.5f, 1.0f);
	renderer->drawBox(
		parent->getPosition().x, parent->getPosition().y + 50.0f,
		100.0f, 12.0f);

	// draw current stats
	renderer->setRenderColour(1.0f, 0.0f, 0.0f, 1.0f);
	renderer->drawBox(
		parent->getPosition().x - 50.0f + m_age->currentPercent * 50.0f,
		parent->getPosition().y + 54.0f,
		m_age->currentPercent * 100.0f, 4.0f);

	renderer->setRenderColour(0.0f, 1.0f, 0.0f, 1.0f);
	renderer->drawBox(
		parent->getPosition().x - 50.0f + m_hunger->currentPercent * 50.0f,
		parent->getPosition().y + 50.0f,
		m_hunger->currentPercent * 100.0f, 4.0f);

	renderer->setRenderColour(0.0f, 0.0f, 1.0f, 1.0f);
	renderer->drawBox(
		parent->getPosition().x - 50.0f + m_energy->currentPercent * 50.0f,
		parent->getPosition().y + 46.0f,
		m_energy->currentPercent * 100.0f, 4.0f);

	renderer->setRenderColour(1.0f, 1.0f, 1.0f, 1.0f);
}

void Life::reset()
{
	m_age->reset();
	m_hunger->reset();
	m_energy->reset();
}