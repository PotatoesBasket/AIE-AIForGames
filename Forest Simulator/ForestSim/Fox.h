#pragma once
#include "Agent.h"

class Sequence;
class Selector;
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
class SeekSteering;
class WanderSteering;

class Fox : public Agent
{
public:
	Fox();
	virtual ~Fox() {}

	void onDraw(std::shared_ptr<aie::Renderer2D> renderer) override;

	void initMovementValues();
	void initBehaviours();

	Node* getNearestFood() override;
	Node* getNearestMate() override;

private:
	std::shared_ptr<Selector> bh_foxActSel;

	std::shared_ptr<Sequence> bh_thirstSeq;
	std::shared_ptr<ThirstCondition> bh_thirstCond;
	std::shared_ptr<NewPathBehaviour> bh_getPathToWater;
	std::shared_ptr<FollowPathBehaviour> bh_followPathToWater;
	std::shared_ptr<DrinkBehaviour> bh_drinkWater;

	std::shared_ptr<Sequence> bh_hungerSeq;
	std::shared_ptr<HungerCondition> bh_hungerCond;
	std::shared_ptr<NewPathBehaviour> bh_getPathToPrey;
	std::shared_ptr<FollowPathBehaviour> bh_followPathToPrey;
	std::shared_ptr<EatBehaviour> bh_eatFood;

	std::shared_ptr<Sequence> bh_energySeq;
	std::shared_ptr<EnergyCondition> bh_energyCond;
	std::shared_ptr<SleepBehaviour> bh_sleep;

	std::shared_ptr<SteeringBehaviour> bh_defaultSteer;

	std::shared_ptr<AvoidSteering> st_avoid;
	std::shared_ptr<SeekSteering> st_seek;
	std::shared_ptr<WanderSteering> st_wander;
};