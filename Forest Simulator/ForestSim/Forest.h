#pragma once
#include <vector>
#include <memory>
#include "Clock.h"

class Animal;
class ObjectPool;

class Forest
{
public:
	Forest();
	~Forest() {}

private:
	Clock clock;

	unsigned int initalBunnyCount = 50;
	unsigned int initalFoxCount = 10;

	//std::unique_ptr<ObjectPool> m_bunnies;
	//std::unique_ptr<ObjectPool> m_foxes;

	//std::vector<std::unique_ptr<Animal>> m_animals;
};