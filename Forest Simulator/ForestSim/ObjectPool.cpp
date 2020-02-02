#include "ObjectPool.h"

ObjectPool::ObjectPool(unsigned int objectCount)
{
	m_totalCount = objectCount;
	m_objectList.reserve(20);

	for (unsigned int i = 0; i < objectCount; ++i)
	{
		m_objectList.push_back(std::make_unique<Animal>());
	}
}

void ObjectPool::activateNext()
{
	std::vector<std::unique_ptr<Animal>>::iterator it = m_objectList.begin();

	while (it != m_objectList.end())
	{
		if ((*it)->IsActive() == false)
		{
			(*it)->reset();
			(*it)->SetActiveState(true);
		}

		++it;
	}
}