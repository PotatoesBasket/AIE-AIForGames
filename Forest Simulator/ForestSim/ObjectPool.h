#pragma once
#include <memory>
#include <vector>
#include <Renderer2D.h>
#include "Animal.h"

class ObjectPool
{
public:
	ObjectPool(unsigned int objectCount);
	~ObjectPool() {}

	void activateNext();

private:
	std::vector<std::unique_ptr<Animal>> m_objectList;
	unsigned int m_totalCount;
};