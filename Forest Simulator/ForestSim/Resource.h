#pragma once
#include "ResourceBase.h"
#include <memory>

template<class T>
class Resource : public ResourceBase
{
public:
	template<typename... Args>
	Resource(const std::string filename, Args... args) : ResourceBase(filename)
	{
		m_data = std::make_unique<T>(filename.c_str(), args...);
	}
	~Resource() {}

	void* getData() { return m_data.get(); }

private:
	std::unique_ptr<T> m_data;
};