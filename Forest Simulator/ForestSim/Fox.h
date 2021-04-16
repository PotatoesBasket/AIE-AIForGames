#pragma once
#include "Agent.h"
#include "Sequence.h"
#include "Selector.h"
#include "Conditions.h"
#include "EatBehaviour.h"
#include "SleepBehaviour.h"
#include "SpawnBehaviour.h"
#include "NewPathBehaviour.h"
#include "FollowPathBehaviour.h"
#include "SteeringBehaviour.h"
#include "AvoidSteering.h"
#include "WanderSteering.h"

class Fox : public Agent
{
public:
	Fox() { init(); }
	Fox(glm::vec2 position) { init(); setPosition(position); }
	virtual ~Fox() {}

	void onDraw(aie::Renderer2D* renderer) override;

	void init();
	void initMovementValues();
	void initBehaviours();

	void spawnNew() override;

	Node* getNearestFood() override;
	Node* getNearestMate() override;

private:
	std::unique_ptr<Selector>				bh_foxActSel;

	std::unique_ptr<Sequence>				bh_hungerSeq;
	std::unique_ptr<HungerCondition>		bh_hungerCond;
	std::unique_ptr<NewPathBehaviour>		bh_getPathToPrey;
	std::unique_ptr<FollowPathBehaviour>	bh_followPathToPrey;
	std::unique_ptr<EatBehaviour>			bh_eat;
		 
	std::unique_ptr<Sequence>				bh_energySeq;
	std::unique_ptr<EnergyCondition>		bh_energyCond;
	std::unique_ptr<SleepBehaviour>			bh_sleep;
		 
	std::unique_ptr<Sequence>				bh_mateSeq;
	std::unique_ptr<MateCondition>			bh_mateCond;
	std::unique_ptr<NewPathBehaviour>		bh_getPathToMate;
	std::unique_ptr<FollowPathBehaviour>	bh_followPathToMate;
	std::unique_ptr<SpawnBehaviour>			bh_spawn;
		 
	std::unique_ptr<SteeringBehaviour>		bh_wander;
	std::unique_ptr<AvoidSteering>			st_avoid;
	std::unique_ptr<WanderSteering>			st_wander;
};