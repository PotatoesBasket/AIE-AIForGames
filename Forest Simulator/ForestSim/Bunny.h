#pragma once
#include "Agent.h"

class Sequence;
class Selector;
class DangerCondition;
class ThirstCondition;
class DrinkBehaviour;
class HungerCondition;
class EatBehaviour;
class EnergyCondition;
class SleepBehaviour;
class NewPathBehaviour;
class FollowPathBehaviour;
class SteeringBehaviour;
class AvoidSteering;
class FleeSteering;
class WanderSteering;

class Bunny : public Agent
{
public:
	Bunny();
	virtual ~Bunny() {}

	void onDraw(std::shared_ptr<aie::Renderer2D> renderer) override;

	void initMovementValues();
	void initBehaviours();

	Node* getNearestFood() override;
	Node* getNearestMate() override;

private:
	std::shared_ptr<Selector> bh_bunnyActSel;

	std::shared_ptr<Sequence> bh_fleeSeq;
	std::shared_ptr<DangerCondition> bh_dangerCond;
	std::shared_ptr<SteeringBehaviour> bh_fleeSteer;

	std::shared_ptr<Sequence> bh_thirstSeq;
	std::shared_ptr<ThirstCondition> bh_thirstCond;
	std::shared_ptr<NewPathBehaviour> bh_getPathToWater;
	std::shared_ptr<FollowPathBehaviour> bh_followPathToWater;
	std::shared_ptr<DrinkBehaviour> bh_drinkWater;

	std::shared_ptr<Sequence> bh_hungerSeq;
	std::shared_ptr<HungerCondition> bh_hungerCond;
	std::shared_ptr<NewPathBehaviour> bh_getPathToGrass;
	std::shared_ptr<FollowPathBehaviour> bh_followPathToGrass;
	std::shared_ptr<EatBehaviour> bh_eatGrass;

	std::shared_ptr<Sequence> bh_energySeq;
	std::shared_ptr<EnergyCondition> bh_energyCond;
	std::shared_ptr<SleepBehaviour> bh_sleep;

	std::shared_ptr<SteeringBehaviour> bh_defaultSteer;

	std::shared_ptr<AvoidSteering> st_avoid;
	std::shared_ptr<FleeSteering> st_flee;
	std::shared_ptr<WanderSteering> st_wander;
};