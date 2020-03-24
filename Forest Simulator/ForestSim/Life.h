#pragma once
#include "GameObject.h"
#include "Stat.h"

// class for holding all animal stats for simulating life
class Life : public Component
{
public:
	Life(float ageRate, float hungerRate, float energyRate);
	virtual ~Life() {}

	void update(GameObject* parent, float deltaTime) override;
	void draw(GameObject* parent, std::shared_ptr<aie::Renderer2D> renderer) override;

	void reset();

	Stat& getAge() { return *m_age.get(); }
	Stat& getHunger() { return *m_hunger.get(); }
	Stat& getEnergy() { return *m_energy.get(); }

private:
	std::unique_ptr<Stat> m_age;
	std::unique_ptr<Stat> m_hunger;
	std::unique_ptr<Stat> m_energy;
};