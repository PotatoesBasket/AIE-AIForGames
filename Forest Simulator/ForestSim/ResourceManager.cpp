#include "ResourceManager.h"

std::shared_ptr<ResourceBase> ResourceManager::loadFont(const std::string filename, int size)
{
	//check if already loaded
	std::vector<std::shared_ptr<ResourceBase>>::iterator it;
	for (it = m_resources.begin(); it != m_resources.end(); ++it)
	{
		//if filename and size match, resource already exists
		if (filename.compare((*it)->getFilename()) == 0 &&
			size == (*it)->as<aie::Font>()->getStringHeight(".") )
		{
			return *it; //return found resource
		}
	}

	//wasn't loaded, create new resource and add to list
	std::shared_ptr<ResourceBase> resource(new Resource<aie::Font>(filename, size));
	m_resources.push_back(resource);
	return resource;
}

std::shared_ptr<ResourceBase> ResourceManager::loadTexture(const std::string filename)
{
	//check if already loaded
	std::vector<std::shared_ptr<ResourceBase>>::iterator it;
	for (it = m_resources.begin(); it != m_resources.end(); ++it)
	{
		if (filename.compare((*it)->getFilename()) == 0)
		{
			return *it;
		}
	}

	//wasn't loaded, create new resource and add to list
	std::shared_ptr<ResourceBase> resource(new Resource<aie::Texture>(filename));
	m_resources.push_back(resource);
	return resource;
}

/*Iterates through resource vector and erases any resources
that are currently only being referenced by the manager.*/
void ResourceManager::collectGarbage()
{
	for (std::vector<std::shared_ptr<ResourceBase>>::iterator it =
		m_resources.begin(); it != m_resources.end();)
	{
		if ((*it).use_count() == 1)
			it = m_resources.erase(it);
		else
			++it;
	}
}