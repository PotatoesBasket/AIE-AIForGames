#pragma once

class DebugManager
{
private:
	DebugManager() {}
	DebugManager(const DebugManager&) {}
	DebugManager& operator=(const DebugManager&) {}

public:
	~DebugManager() {}

	static DebugManager& current();

	void getInput();
	void printData();

	void toggleShowAll(bool isShowing);

	bool showPaths = false;
	bool showNodes = false;
	bool showQuadtree = false;
	bool showBehaviourStates = false;
	bool printDebugStats = false;

	int noOfEating = 0;
	int noOfSleeping = 0;
	int noOfSpawning = 0;
	int noOfFollowingPath = 0;
	int noOfFindingNewPath = 0;
	int noOfSteering = 0;

	double totalFuncTimePathing = 0;
	double totalFuncTimeBehaviour = 0;
};