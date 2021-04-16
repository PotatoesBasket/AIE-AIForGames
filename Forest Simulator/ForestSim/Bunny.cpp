#include "Bunny.h"
#include "Map.h"
#include "Life.h"
#include "Grass.h"
#include <glm/gtx/norm.hpp>

void Bunny::onDraw(aie::Renderer2D* renderer)
{
	renderer->setRenderColour(0, 0, 1, 1);
	renderer->drawCircle(getPosition().x, getPosition().y, 10);
	renderer->setRenderColour(1, 1, 1, 1);

#ifndef NDEBUG
	// draw velocity vector
	renderer->setRenderColour(1, 0, 0, 1);
	renderer->drawLine(getPosition().x, getPosition().y,
		getPosition().x + m_velocity.x, getPosition().y + m_velocity.y, 2);

	//draw path of nodes
	renderer->setRenderColour(1, 0, 1, 1);
	if (m_path.size() > 0)
		for (auto& node : m_path)
			renderer->drawCircle(node->position.x, node->position.y, 5);

	renderer->setRenderColour(1, 1, 1, 1);
#endif
}

void Bunny::init()
{
	m_life = std::make_shared<Life>(0.008f, 0.028f, 0.02f);
	addComponent(m_life);

	initMovementValues();
	initBehaviours();
}

void Bunny::initMovementValues()
{
	m_maxVelocity = 400;
	m_maxForce = 100;
	m_visionRange = 18;
	m_maxAvoidForce = 500;
	m_matureAge = 0.05f;
	m_respawnDelay = 20;

	RNG& rng = RNG::getInstance();
	rng.setFloatRange(0, 20);
	m_respawnTimer = rng.nextFloat();
}

void Bunny::initBehaviours()
{
	// [selector] actions
	bh_bunnyActSel = std::make_unique<Selector>();
	addBehaviour(bh_bunnyActSel.get());
		// [sequence] flee
		bh_fleeSeq = std::make_unique<Sequence>();
		bh_bunnyActSel->addBehaviour(bh_fleeSeq.get());
			// [condition] check if predator nearby
			bh_dangerCond = std::make_unique<DangerCondition>();
			bh_fleeSeq->addBehaviour(bh_dangerCond.get());
			// [action] flee
			bh_flee = std::make_unique<SteeringBehaviour>();
			bh_fleeSeq->addBehaviour(bh_flee.get());
				// [steer] avoid obstacles
				st_avoidFlee = std::make_unique<AvoidSteering>();
				bh_flee->addSteeringForce(st_avoidFlee.get());
				// [steer] flee from predator
				st_flee = std::make_unique<FleeSteering>();
				bh_flee->addSteeringForce(st_flee.get());
		// [sequence] hunger
		bh_hungerSeq = std::make_unique<Sequence>();
		bh_bunnyActSel->addBehaviour(bh_hungerSeq.get());
			// [condition] check hunger level
			bh_hungerCond = std::make_unique<HungerCondition>();
			bh_hungerSeq->addBehaviour(bh_hungerCond.get());
			// [action] find nearest food source
			bh_getPathToGrass = std::make_unique<NewPathBehaviour>(m_targetNode);
			bh_hungerSeq->addBehaviour(bh_getPathToGrass.get());
			// [action] travel to food source
			bh_followPathToGrass = std::make_unique<FollowPathBehaviour>();
			bh_hungerSeq->addBehaviour(bh_followPathToGrass.get());
			// [action] eat
			bh_eat = std::make_unique<EatBehaviour>();
			bh_hungerSeq->addBehaviour(bh_eat.get());
		// [sequence] energy
		bh_energySeq = std::make_unique<Sequence>();
		bh_bunnyActSel->addBehaviour(bh_energySeq.get());
			// [condition] check energy level
			bh_energyCond = std::make_unique<EnergyCondition>();
			bh_energySeq->addBehaviour(bh_energyCond.get());
			// [action] sleep
			bh_sleep = std::make_unique<SleepBehaviour>();
			bh_energySeq->addBehaviour(bh_sleep.get());
		// [sequence] breeding
		bh_mateSeq = std::make_unique<Sequence>();
		bh_bunnyActSel->addBehaviour(bh_mateSeq.get());
			// [condition] check for nearest viable partner
			bh_mateCond = std::make_unique<MateCondition>();
			bh_mateSeq->addBehaviour(bh_mateCond.get());
			// [action] get path to partner
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
		bh_bunnyActSel->addBehaviour(bh_wander.get());
			// [steer] avoid obstacles
			st_avoidWander = std::make_unique<AvoidSteering>();
			bh_wander->addSteeringForce(st_avoidFlee.get());
			// [steer] wander randomly
			st_wander = std::make_unique<WanderSteering>();
			bh_wander->addSteeringForce(st_wander.get());
}

void Bunny::spawnNew()
{
	m_currentMap->getBunnyPool()->activateNext(getPosition());
}

Node* Bunny::getNearestFood()
{
	if (getMap()->getGrass().begin() == getMap()->getGrass().end())
		return nullptr;

	std::vector<GameObject*> nearestGrassList;
	Quadtree* grassTree = getMap()->getGrassTree();
	grassTree->query(getPosition(), 9999999, nearestGrassList);

	Grass* closestGrass = nullptr;

	for (auto& g : nearestGrassList)
	{
		Grass* grass = dynamic_cast<Grass*>(g);

		// skip if inactive
		if (!grass->isEdible())
			continue;

		// if no closest is set yet, set it and skip comparison
		if (closestGrass == nullptr)
			closestGrass = grass;
		// otherwise, compare with current closest
		else if (glm::length2(grass->getPosition() - getPosition()) < glm::length2(closestGrass->getPosition() - getPosition()))
			closestGrass = grass;
	}

	// check grass was found, return node grass is on
	if (closestGrass != nullptr)
	{
		m_targetGrass = closestGrass;
		return getMap()->getNodeAtPosition(closestGrass->getPosition());
	}

	m_targetGrass = nullptr;
	return nullptr;
}

Node* Bunny::getNearestMate()
{
	if (getMap()->getBunnies().begin() == getMap()->getBunnies().end())
		return nullptr;

	std::vector<GameObject*> nearestList;
	Quadtree* objTree = getMap()->getBunnyTree();
	objTree->query(getPosition(), 9999999, nearestList);

	Agent* closestMate = nullptr;

	for (auto& obj : nearestList)
	{
		Bunny* bunny = dynamic_cast<Bunny*>(obj);

		// skip if inactive
		if (!bunny->isActive())
			continue;

		// skip if bunny is this bunny
		if (bunny == this)
			continue;

		// skip if partner ineligible
		if (!bunny->canSpawn())
			continue;

		// if no closest is set yet, set it and skip comparison
		if (closestMate == nullptr)
			closestMate = bunny;
		// otherwise, compare with current closest
		else if (glm::length2(bunny->getPosition() - getPosition()) < glm::length2(closestMate->getPosition() - getPosition()))
			closestMate = bunny;
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