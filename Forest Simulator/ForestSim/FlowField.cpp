#include "FlowField.h"
#include "GameObject.h"
#include "ColourDefines.h"
#include <list>

void FlowField::randomiseLevel(float obstaclePercentage)
{
	//randomly place obstacles
	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			//a really bad random percentage calculator
			if (rand() % 100 < int(100 * obstaclePercentage))
				m_costField[r][c] = Costs::IMPASSABLE;
			else
				m_costField[r][c] = Costs::WALKABLE;

			m_integrationField[r][c] = 0;
			m_flowField[r][c].x = 0;
			m_flowField[r][c].y = 0;
		}
	}
}

void FlowField::placeGameObjects(std::vector<std::shared_ptr<GameObject>> objects)
{
	//safely place game objects
	for (auto& object : objects)
	{
		int index = 0;

		do
		{
			index = rand() % (ROWS * COLS);
		}
		while (m_costField[index / COLS][index % COLS] == Costs::IMPASSABLE);

		Vector2 position = Vector2(
			CELLSIZE * 0.5f + (index % COLS) * CELLSIZE,
			CELLSIZE * 0.5f + (index / COLS) * CELLSIZE);

		object->setPosition(position);
	}
}

void FlowField::setGoal(int x, int y)
{
	x /= CELLSIZE;
	y /= CELLSIZE;

	if (m_integrationField[y][x] != Costs::IMPASSABLE)
	{
		performIntergration(x, y);
		generateFlowField();
	}
}

void FlowField::getCellNeighbours(int x, int y, std::vector<int>& neighbours)
{
	neighbours.clear();

	// 8 potential neighbours
	// to do: this could be improved by ignoring diagonal neighbours that should be blocked by impassable cells
	for (int r = -1; r <= 1; ++r)
	{
		for (int c = -1; c <= 1; ++c)
		{
			if (x == c &&
				y == r)
				continue;

			if ((x + c) >= 0 &&
				(x + c) <= (COLS - 1) &&
				(y + r) >= 0 &&
				(y + r) <= (ROWS - 1) &&
				m_costField[y + r][x + c] != Costs::IMPASSABLE)
			{
				neighbours.push_back(x + c);
				neighbours.push_back(y + r);
			}
		}
	}
}

void FlowField::performIntergration(int goalX, int goalY)
{
	// perform a dijkstra's search towards goal cell, 
	// starting from goal cell spreading outwards

	// reset integration field
	for (int r = 0; r < ROWS; ++r)
		for (int c = 0; c < COLS; ++c)
			m_integrationField[r][c] = FLT_MAX;

	// push goal into open list
	std::list<std::pair<int, int>> openList;
	openList.push_front({ goalX, goalY });

	m_integrationField[goalY][goalX] = 0;

	std::vector<int> neighbours(16);

	// do search
	while (openList.empty() == false)
	{
		auto current = openList.front();
		openList.pop_front();

		// get neighbours of popped cell and iterate over them
		getCellNeighbours(current.first, current.second, neighbours);

		unsigned int neighbourCount = neighbours.size();

		for (unsigned int i = 0; i < neighbourCount; i += 2)
		{
			// calculate new travel cost
			// current is a std::pair<int, int> representing x and y
			float cost = m_integrationField[current.second][current.first] +
				m_costField[neighbours[i + 1]][neighbours[i]];

			// compare if score was lower
			if (cost < m_integrationField[neighbours[i + 1]][neighbours[i]])
			{
				// create a new std::pair for the neighbour
				std::pair<int, int> neighbour = { neighbours[i], neighbours[i + 1] };

				// check if they should be added to the open list
				auto iter = std::find(openList.begin(), openList.end(), neighbour);

				if (iter == openList.end())
					openList.push_back(neighbour);

				// update the cost
				m_integrationField[neighbours[i + 1]][neighbours[i]] = cost;
			}
		}
	}
}

void FlowField::generateFlowField()
{
	// for each grid cell, sample neighbour costs and 
	// setup flow direction to lowest cost neighbour

	std::vector<int> neighbours;
	int lowestX, lowestY;
	float lowestScore;
	bool foundNeighbour = false;

	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			// reset field
			m_flowField[r][c].x = 0;
			m_flowField[r][c].y = 0;

			// reset lowest score
			lowestScore = FLT_MAX;

			// gather neighbours
			getCellNeighbours(c, r, neighbours);

			unsigned int neighbourCount = neighbours.size();

			// only set a vector if neighbours found
			foundNeighbour = false;
			if (neighbourCount > 0)
			{
				for (unsigned int i = 0; i < neighbourCount; i += 2)
				{
					int nx = neighbours[i];
					int ny = neighbours[i + 1];

					// is it lowest?
					if (m_integrationField[ny][nx] < lowestScore)
					{
						lowestScore = m_integrationField[ny][nx];
						lowestX = nx;
						lowestY = ny;
						foundNeighbour = true;
					}
				}

				// if valid neighbour found, normalise direction
				if (foundNeighbour)
				{
					float mag = float(
						(lowestX - c) * (lowestX - c) +
						(lowestY - r) * (lowestY - r));

					if (mag > 0)
					{
						mag = sqrt(mag);
						m_flowField[r][c].x = (lowestX - c) / mag;
						m_flowField[r][c].y = (lowestY - r) / mag;
					}
				}
			}
		}
	}
}

void FlowField::draw(std::shared_ptr<aie::Renderer2D> renderer)
{
	for (int r = 0; r < ROWS; ++r)
	{
		for (int c = 0; c < COLS; ++c)
		{
			if (m_costField[r][c] == IMPASSABLE)
			{
				renderer->setRenderColour(HEX_CYAN);
				renderer->drawBox(c * CELLSIZE + CELLSIZE / 2, r * CELLSIZE + CELLSIZE / 2, CELLSIZE, CELLSIZE);
				renderer->setRenderColour(HEX_BLACK);
			}
		}
	}
}