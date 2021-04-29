#include "DebugManager.h"
#include <Input.h>
#include <iostream>
#include <Windows.h>

DebugManager& DebugManager::current()
{
	static DebugManager instance;
	return instance;
}

void DebugManager::getInput()
{
	aie::Input* getInput = aie::Input::getInstance();

	if (getInput->wasKeyPressed(aie::INPUT_KEY_1))
		toggleShowAll(true);
	if (getInput->wasKeyPressed(aie::INPUT_KEY_2))
		toggleShowAll(false);
	if (getInput->wasKeyPressed(aie::INPUT_KEY_3))
		showPaths = !showPaths;
	if (getInput->wasKeyPressed(aie::INPUT_KEY_4))
		showNodes = !showNodes;
	if (getInput->wasKeyPressed(aie::INPUT_KEY_5))
		showQuadtree = !showQuadtree;
	if (getInput->wasKeyPressed(aie::INPUT_KEY_6))
		showBehaviourStates = !showBehaviourStates;
	if (getInput->wasKeyPressed(aie::INPUT_KEY_0))
		printDebugStats = !printDebugStats;
}

void DebugManager::printData()
{
	if (printDebugStats)
	{
		std::cout << "\x1b[0J"
			<< "No. of agents eating: " << noOfEating << "\n"
			<< "No. of agents sleeping: " << noOfSleeping << "\n"
			<< "No. of agents spawning: " << noOfSpawning << "\n"
			<< "No. of agents following path: " << noOfFollowingPath << "\n"
			<< "No. of agents getting new path: " << noOfFindingNewPath << "\n"
			<< "No. of agents steering: " << noOfSteering << "\n"
			<< "Total pathfinding time:" << totalFuncTimePathing << "\n"
			<< "Total behaviour tree time:" << totalFuncTimeBehaviour << "\n";

		noOfEating = 0;
		noOfSleeping = 0;
		noOfSpawning = 0;
		noOfFollowingPath = 0;
		noOfFindingNewPath = 0;
		noOfSteering = 0;
		totalFuncTimePathing = 0;
		totalFuncTimeBehaviour = 0;
	}
}

void DebugManager::toggleShowAll(bool isShowing)
{
	showPaths = isShowing;
	showNodes = isShowing;
	showQuadtree = isShowing;
	showBehaviourStates = isShowing;
	printDebugStats = isShowing;
}