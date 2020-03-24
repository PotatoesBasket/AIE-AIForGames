#include "Life.h"
#include "RNG.h"

Life::Life(float ageRate, float hungerRate, float energyRate)
{
	m_age = std::make_unique<Stat>(ageRate);
	m_hunger = std::make_unique<Stat>(hungerRate);
	m_energy = std::make_unique<Stat>(energyRate);

	RNG& rng = RNG::getInstance();
	rng.setFloatRange(0, 0.5f);

	m_age->manualSet(rng.nextFloat());
	m_hunger->manualSet(rng.nextFloat());
	m_energy->manualSet(rng.nextFloat());
}

void Life::update(GameObject* parent, float deltaTime)
{
	m_age->update(deltaTime);
	m_hunger->update(deltaTime);
	m_energy->update(deltaTime);

	// kill parent if a stat gets maxed
	if (m_age->getCurrentPercent() >= 1 ||
		m_hunger->getCurrentPercent() >= 1 ||
		m_energy->getCurrentPercent() >= 1)
		parent->setActiveState(false);
}

void Life::draw(GameObject* parent, std::shared_ptr<aie::Renderer2D> renderer)
{
	// draw stat sliders above parent in grey
	renderer->setRenderColour(0.5f, 0.5f, 0.5f, 1);
	renderer->drawBox(
		parent->getPosition().x, parent->getPosition().y + 50,
		100, 12);

	// draw current stats
	renderer->setRenderColour(1, 0, 0, 1);
	renderer->drawBox(
		parent->getPosition().x - 50 + m_age->getCurrentPercent() * 50,
		parent->getPosition().y + 54,
		m_age->getCurrentPercent() * 100, 4);

	renderer->setRenderColour(0, 1, 0, 1);
	renderer->drawBox(
		parent->getPosition().x - 50 + m_hunger->getCurrentPercent() * 50,
		parent->getPosition().y + 50,
		m_hunger->getCurrentPercent() * 100, 4);

	renderer->setRenderColour(0, 0, 1, 1);
	renderer->drawBox(
		parent->getPosition().x - 50 + m_energy->getCurrentPercent() * 50,
		parent->getPosition().y + 46,
		m_energy->getCurrentPercent() * 100, 4);

	renderer->setRenderColour(1, 1, 1, 1);
}

void Life::reset()
{
	m_age->reset();
	m_hunger->reset();
	m_energy->reset();
}