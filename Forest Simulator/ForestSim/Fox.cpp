#include "Fox.h"
#include "Map.h"
#include "Life.h"
#include "Sequence.h"
#include "Selector.h"
#include "Conditions.h"
#include "EatBehaviour.h"
#include "SleepBehaviour.h"
#include "NewPathBehaviour.h"
#include "FollowPathBehaviour.h"
#include "SteeringBehaviour.h"
#include "AvoidSteering.h"
#include "SeekSteering.h"
#include "WanderSteering.h"

Fox::Fox()
{
	m_life = std::make_shared<Life>(/*0.003f, 0.018f, 0.016f*/0, 0.005f, 0.002f);
	addComponent(m_life);

	initMovementValues();
	initBehaviours();
}

void Fox::onDraw(std::shared_ptr<aie::Renderer2D> renderer)
{
	renderer->setRenderColour(1, 0, 0, 1);
	renderer->drawCircle(getPosition().x, getPosition().y, 15);
	renderer->setRenderColour(1, 1, 1, 1);

#ifndef NDEBUG
	// draw velocity vector
	renderer->setRenderColour(1, 0, 0, 1);
	renderer->drawLine(getPosition().x, getPosition().y,
		getPosition().x + m_velocity.x, getPosition().y + m_velocity.y, 2);
	renderer->setRenderColour(1, 1, 1, 1);

	renderer->setRenderColour(1, 1, 0, 1);
	if (m_path.size() > 0)
		for (auto& node : m_path)
			renderer->drawCircle(node->position.x, node->position.y, 5);
	renderer->setRenderColour(1, 1, 1, 1);
#endif
}

void Fox::initMovementValues()
{
	m_maxVelocity = 400;
	m_maxForce = 100;
	m_visionRange = 9;
	m_maxAvoidForce = 400;
}

void Fox::initBehaviours()
{
	// [selector] actions
	bh_foxActSel = std::make_shared<Selector>();
	addBehaviour(bh_foxActSel);
		// [sequence] hunger
		bh_hungerSeq = std::make_shared<Sequence>();
		bh_foxActSel->addBehaviour(bh_hungerSeq);
			// [condition] check hunger level
			bh_hungerCond = std::make_shared<HungerCondition>();
			bh_hungerSeq->addBehaviour(bh_hungerCond);
			// [action] find nearest prey animal
			bh_getPathToPrey = std::make_shared<NewPathBehaviour>(m_targetNode);
			bh_hungerSeq->addBehaviour(bh_getPathToPrey);
			// [action] chase prey
			bh_followPathToPrey = std::make_shared<FollowPathBehaviour>();
			bh_hungerSeq->addBehaviour(bh_followPathToPrey);
			// [action] eat
			bh_eatFood = std::make_shared<EatBehaviour>();
			bh_hungerSeq->addBehaviour(bh_eatFood);
		// [sequence] energy
		bh_energySeq = std::make_shared<Sequence>();
		bh_foxActSel->addBehaviour(bh_energySeq);
			// [condition] check energy level
			bh_energyCond = std::make_shared<EnergyCondition>();
			bh_energySeq->addBehaviour(bh_energyCond);
			// [action] sleep
			bh_sleep = std::make_shared<SleepBehaviour>();
			bh_energySeq->addBehaviour(bh_sleep);
		// [sequence] breeding
			// [condition] check if ready for breeding
			// [action] get path to nearest viable partner
			// [action] travel to partner
			// [action] spawn young
		// [action] wander
		bh_defaultSteer = std::make_shared<SteeringBehaviour>();
		bh_foxActSel->addBehaviour(bh_defaultSteer);
			// [steer] avoid obstacles
			st_avoid = std::make_shared<AvoidSteering>();
			bh_defaultSteer->addSteeringForce(st_avoid);
			// [steer] wander
			st_wander = std::make_shared<WanderSteering>();
			bh_defaultSteer->addSteeringForce(st_wander);
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
			closestPrey = prey.get();
		// otherwise, compare with current closest
		else if (getPosition().distanceSqr(prey->getPosition()) <
			getPosition().distanceSqr(prey->getPosition()))
			closestPrey = prey.get();
	}

	// check prey was found, return node prey is on
	if (closestPrey != nullptr)
	{
		m_targetAgent = closestPrey;
		return getMap()->getNodeAtPosition(closestPrey->getPosition());
	}

	return nullptr;
}

Node* Fox::getNearestMate()
{
	Node* mate = nullptr;

	return mate;
}