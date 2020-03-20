#include "Bunny.h"
#include "Map.h"
#include "Life.h"
#include "Grass.h"
#include "Sequence.h"
#include "Selector.h"
#include "Conditions.h"
#include "EatBehaviour.h"
#include "SleepBehaviour.h"
#include "NewPathBehaviour.h"
#include "FollowPathBehaviour.h"
#include "SteeringBehaviour.h"
#include "AvoidSteering.h"
#include "FleeSteering.h"
#include "WanderSteering.h"

Bunny::Bunny()
{
	m_life = std::make_shared<Life>(0.009f, 0.02f, 0.014f);
	addComponent(m_life);

	initMovementValues();
	//initBehaviours();
}

void Bunny::onDraw(std::shared_ptr<aie::Renderer2D> renderer)
{
	renderer->setRenderColour(0, 0, 1, 1);
	renderer->drawCircle(getPosition().x, getPosition().y, 10);
	renderer->setRenderColour(1, 1, 1, 1);

#ifndef NDEBUG
	// draw velocity vector
	renderer->setRenderColour(1, 0, 0, 1);
	renderer->drawLine(getPosition().x, getPosition().y,
		getPosition().x + m_velocity.x, getPosition().y + m_velocity.y, 2);
	renderer->setRenderColour(1, 1, 1, 1);
#endif
}

void Bunny::initMovementValues()
{
	m_maxVelocity = 800;
	m_maxForce = 300;
	m_visionRange = 8;
	m_maxAvoidForce = 600;
	m_fleeRange = 100;
}

void Bunny::initBehaviours()
{
	st_avoid = std::make_shared<AvoidSteering>();
	st_flee = std::make_shared<FleeSteering>();
	st_wander = std::make_shared<WanderSteering>();

	st_flee->setTarget(m_targetAgent);

	// [selector] actions
	bh_bunnyActSel = std::make_shared<Selector>();
	addBehaviour(bh_bunnyActSel);
		// [sequence] flee
		bh_fleeSeq = std::make_shared<Sequence>();
		bh_bunnyActSel->addBehaviour(bh_fleeSeq);
			// [condition] check if predator nearby
			bh_dangerCond = std::make_shared<DangerCondition>();
			bh_fleeSeq->addBehaviour(bh_dangerCond);
			// [action] flee
			bh_fleeSteer = std::make_shared<SteeringBehaviour>();
				// [steer] avoid obstacles
				bh_fleeSteer->addSteeringForce(st_avoid);
				// [steer] flee from predator
				bh_fleeSteer->addSteeringForce(st_flee);
		// [sequence] hunger
		bh_hungerSeq = std::make_shared<Sequence>();
		bh_bunnyActSel->addBehaviour(bh_hungerSeq);
			// [condition] check hunger level
			bh_hungerCond = std::make_shared<HungerCondition>();
			bh_hungerSeq->addBehaviour(bh_hungerCond);
			// [action] find nearest food source
			bh_getPathToGrass = std::make_shared<NewPathBehaviour>(getNearestFood());
			bh_hungerSeq->addBehaviour(bh_getPathToGrass);
			// [action] travel to food source
			bh_followPathToGrass = std::make_shared<FollowPathBehaviour>();
			bh_hungerSeq->addBehaviour(bh_followPathToGrass);
			// [action] eat
			bh_eatGrass = std::make_shared<EatBehaviour>();
			bh_hungerSeq->addBehaviour(bh_eatGrass);
		// [sequence] energy
		bh_energySeq = std::make_shared<Sequence>();
		bh_bunnyActSel->addBehaviour(bh_energySeq);
			// [condition] check energy level
			bh_energyCond = std::make_shared<EnergyCondition>();
			bh_energySeq->addBehaviour(bh_energyCond);
			// [action] sleep
			bh_sleep = std::make_shared<SleepBehaviour>();
			bh_energySeq->addBehaviour(bh_sleep);
		// [sequence] breeding
			// [condition] check for nearest viable partner
			// [action] travel to partner
			// [action] spawn young
		// [action] wander
		bh_defaultSteer = std::make_shared<SteeringBehaviour>();
		bh_bunnyActSel->addBehaviour(bh_defaultSteer);
			// [steer] avoid obstacles
			bh_defaultSteer->addSteeringForce(st_avoid);
			// [steer] wander randomly
			bh_defaultSteer->addSteeringForce(st_wander);
}

Node* Bunny::getNearestFood()
{
	Node* food = nullptr;

	return food;
}

Node* Bunny::getNearestMate()
{
	Node* mate = nullptr;

	return mate;
}