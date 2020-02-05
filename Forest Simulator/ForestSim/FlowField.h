#pragma once
#include <vector>
#include <memory>
#include <Renderer2D.h>

#ifndef NDEBUG
#include <Debug/MathLibrary.h>
#else
#include <Release/MathLibrary.h>
#endif

class GameObject;

class FlowField
{
public:
	enum Costs : unsigned short
	{
		WALKABLE = 1,
		IMPASSABLE = 0xFFFF,
	};

	enum Size
	{
		ROWS = 23,
		COLS = 40,
		CELLSIZE = 32,
	};

	FlowField() {}
	FlowField(float obstaclePercentage) { randomiseLevel(obstaclePercentage); }
	~FlowField() {}

	void randomiseLevel(float obstaclePercentage); //randomly generates map and obstacles
	void placeGameObjects(std::vector<std::shared_ptr<GameObject>> objects); //set agents on map
	void setGoal(int x, int y); //set current goal for agents
	Vector2* getFlowField() { return &m_flowField[0][0]; }

	void draw(std::shared_ptr<aie::Renderer2D> renderer);

private:
	void getCellNeighbours(int x, int y, std::vector<int>& neighbours);
	void performIntergration(int goalX, int goalY);
	void generateFlowField();

	unsigned short m_costField[ROWS][COLS]; //contains movement costs through the field
	float m_integrationField[ROWS][COLS]; //contains actual travel cost to goal cell
	Vector2 m_flowField[ROWS][COLS]; //the vector flow field that travels towards the goal cell
};