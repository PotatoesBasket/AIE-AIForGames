#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "ObjectPool.h"
#include "Map.h"
#include "RNG.h"
#include "ScreenDefines.h"

class ForestSimApp : public aie::Application
{
public:
	ForestSimApp() {}
	virtual ~ForestSimApp() {}

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void camControls(float deltaTime);

protected:
	Vector2 m_camPos;
	float m_currentPanSpeed = 400;
	const float m_panSpeed = 400;
	const float m_fastPanSpeed = 800;

	bool m_zoomInputPressed = false;
	bool m_zoomedOut = false;

	std::shared_ptr<aie::Renderer2D> m_2dRenderer = nullptr;

	std::unique_ptr<Map> m_map = nullptr;
	std::unique_ptr<ObjectPool> m_bunnyPool = nullptr;
};