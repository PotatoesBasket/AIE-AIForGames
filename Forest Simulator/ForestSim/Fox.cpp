#include "Fox.h"
#include "Map.h"
#include "Life.h"
#include <glm/gtx/norm.hpp>

void Fox::onDraw(std::shared_ptr<aie::Renderer2D> renderer)
{
	renderer->setRenderColour(1, 0, 0, 1);
	renderer->drawCircle(getPosition().x, getPosition().y, 15);
	renderer->setRenderColour(1, 1, 1, 1);

#ifndef NDEBUG
	// draw velocity vector
	renderer->setRenderColour(0, 0, 1, 1);
	renderer->drawLine(getPosition().x, getPosition().y,
		getPosition().x + m_velocity.x, getPosition().y + m_velocity.y, 2);

	//draw path of nodes
	renderer->setRenderColour(1, 1, 0, 1);
	if (m_path.size() > 0)
		for (auto& node : m_path)
			renderer->drawCircle(node->position.x, node->position.y, 5);

	renderer->setRenderColour(1, 1, 1, 1);
#endif
}

void Fox::init()
{
	m_life = std::make_shared<Life>(0.003f, 0.014f, 0.01f);
	addComponent(m_life);

	initMovementValues();
	initBehaviours();
}

void Fox::initMovementValues()
{
	m_maxVelocity = 600;
	m_maxForce = 100;
	m_visionRange = 9;
	m_maxAvoidForce = 600;
	m_matureAge = 0.3f;
	m_respawnDelay = 40;

	RNG& rng = RNG::getInstance();
	rng.setFloatRange(0, 40);
	m_respawnTimer = rng.nextFloat();
}

void Fox::initBehaviours()
{
	// [selector] actions
	bh_foxActSel = std::make_unique<Selector>();
	addBehaviour(bh_foxActSel.get());
		// [sequence] hunger
		bh_hungerSeq = std::make_unique<Sequence>();
		bh_foxActSel->addBehaviour(bh_hungerSeq.get());
			// [condition] check hunger level
			bh_hungerCond = std::make_unique<HungerCondition>();
			bh_hungerSeq->addBehaviour(bh_hungerCond.get());
			// [action] get path to nearest prey animal
			bh_getPathToPrey = std::make_unique<NewPathBehaviour>(m_targetNode);
			bh_hungerSeq->addBehaviour(bh_getPathToPrey.get());
			// [action] follow path to prey
			bh_followPathToPrey = std::make_unique<FollowPathBehaviour>();
			bh_hungerSeq->addBehaviour(bh_followPathToPrey.get());
			// [action] eat
			bh_eat = std::make_unique<EatBehaviour>();
			bh_hungerSeq->addBehaviour(bh_eat.get());
		// [sequence] energy
		bh_energySeq = std::make_unique<Sequence>();
		bh_foxActSel->addBehaviour(bh_energySeq.get());
			// [condition] check energy level
			bh_energyCond = std::make_unique<EnergyCondition>();
			bh_energySeq->addBehaviour(bh_energyCond.get());
			// [action] sleep
			bh_sleep = std::make_unique<SleepBehaviour>();
			bh_energySeq->addBehaviour(bh_sleep.get());
		// [sequence] breeding
		bh_mateSeq = std::make_unique<Sequence>();
		bh_foxActSel->addBehaviour(bh_mateSeq.get());
			// [condition] check if ready for breeding
			bh_mateCond = std::make_unique<MateCondition>();
			bh_mateSeq->addBehaviour(bh_mateCond.get());
			// [action] get path to nearest viable partner
			bh_getPathToMate = std::make_unique<NewPathBehaviour>(m_targetNode);
			bh_mateSeq->addBehaviour(bh_getPathToMate.get());
			// [action] follow path to partner
			bh_followPathToMate = std::make_unique<FollowPathBehaviour>();
			bh_mateSeq->addBehaviour(bh_followPathToMate.get());
			// [action] spawn young
			bh_spawn = std::make_unique<SpawnBehaviour>();
			bh_mateSeq->addBehaviour(bh_spawn.get());
		// [action] wander
		bh_wander = std::make_unique<SteeringBehaviour>();
		bh_foxActSel->addBehaviour(bh_wander.get());
			// [steer] avoid obstacles
			st_avoid = std::make_unique<AvoidSteering>();
			bh_wander->addSteeringForce(st_avoid.get());
			// [steer] wander
			st_wander = std::make_unique<WanderSteering>();
			bh_wander->addSteeringForce(st_wander.get());
}

void Fox::spawnNew()
{
	m_currentMap->getFoxPool()->activateNext(getPosition());
}

Node* Fox::getNearestFood()
{
	if (getMap()->getBunnies().begin() == getMap()->getBunnies().end())
		return nullptr;

	Agent* closestPrey = nullptr;

	for (auto& prey : getMap()->getBunnies())
	{
		// skip if inactive
		if (!prey->isActive())
			continue;

		// if no closest is set yet, set it and skip comparison
		if (closestPrey == nullptr)
			closestPrey = prey;
		// otherwise, compare with current closest
		else if (glm::length2(prey->getPosition() - getPosition()) < glm::length2(closestPrey->getPosition() - getPosition()))
			closestPrey = prey;
	}

	// check prey was found, return node prey is on
	if (closestPrey != nullptr)
	{
		m_targetAgent = closestPrey;
		return getMap()->getNodeAtPosition(closestPrey->getPosition());
	}

	m_targetAgent = nullptr;
	return nullptr;
}

Node* Fox::getNearestMate()
{
	if (getMap()->getFoxes().begin() == getMap()->getFoxes().end())
		return nullptr;

	Agent* closestMate = nullptr;

	for (auto& fox : getMap()->getFoxes())
	{
		// skip if inactive
		if (!fox->isActive())
			continue;

		// skip if fox is this fox
		if (fox == this)
			continue;

		// skip if partner ineligible
		if (!fox->canSpawn())
			continue;

		// if no closest is set yet, set it and skip comparison
		if (closestMate == nullptr)
			closestMate = fox;
		// otherwise, compare with current closest
		else if (glm::length2(fox->getPosition() - getPosition()) < glm::length2(closestMate->getPosition() - getPosition()))
			closestMate = fox;
	}

	// check mate was found, return node mate is on
	if (closestMate != nullptr)
	{
		m_targetAgent = closestMate;
		return getMap()->getNodeAtPosition(closestMate->getPosition());
	}

	m_targetAgent = nullptr;
	return nullptr;
}