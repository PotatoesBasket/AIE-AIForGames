#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "Map.h"
#include "Bunny.h"
#include "Fox.h"
#include "DebugManager.h"

class ForestSimApp : public aie::Application
{
public:
	ForestSimApp() {}
	virtual ~ForestSimApp() {}

	virtual bool startup();
	virtual void shutdown() {}

	virtual void update(float deltaTime);
	virtual void draw();

private:
	void initCamera();
	void camControls(float deltaTime);

	float cappedDeltaTime(float deltaTime) { return deltaTime < m_deltaLimit ? deltaTime : m_deltaLimit; }

protected:
	std::unique_ptr<aie::Renderer2D> m_2dRenderer = nullptr;
	std::unique_ptr<Map> m_map = nullptr;
	DebugManager& m_debug = DebugManager::current();

	float m_deltaLimit = 0.3f;

	glm::vec2 m_camPos = glm::vec2(0.0f);
	float m_currentPanSpeed = 0.0f;
	const float m_panSpeed = 400.0f;
	const float m_fastPanSpeed = 1000.0f;
	unsigned int m_zoomLevel = 1;

	bool m_zoomInputPressed = false;
};