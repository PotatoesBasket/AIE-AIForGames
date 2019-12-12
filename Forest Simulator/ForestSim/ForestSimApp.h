#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <memory>

class ForestSimApp : public aie::Application
{
public:
	ForestSimApp() {}
	virtual ~ForestSimApp() {}

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:
	std::shared_ptr<aie::Renderer2D> m_2dRenderer = nullptr;
	std::shared_ptr<aie::Font> m_font = nullptr;
};