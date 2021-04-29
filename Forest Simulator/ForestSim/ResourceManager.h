#pragma once
#include "Resource.h"
#include <Font.h>
#include <Texture.h>
#include <vector>

class ResourceManager
{
private:
	ResourceManager() {}
	ResourceManager(const ResourceManager&) {}
	ResourceManager& operator=(const ResourceManager&) {}

public:
	~ResourceManager() {}

	static ResourceManager& getInstance();

	size_t getCount() const { return m_resources.size(); }

	std::shared_ptr<ResourceBase> loadFont(const std::string filename, int size);
	std::shared_ptr<ResourceBase> loadTexture(const std::string filename);

	void collectGarbage();

private:
	std::vector<std::shared_ptr<ResourceBase>> m_resources;
};