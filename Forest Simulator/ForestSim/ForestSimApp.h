#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "Map.h"
#include "Bunny.h"
#include "Fox.h"

class ForestSimApp : public aie::Application
{
public:
	ForestSimApp() {}
	virtual ~ForestSimApp() { delete m_map; }

	virtual bool startup();
	virtual void shutdown() {}

	virtual void update(float deltaTime);
	virtual void draw();

private:
	void initCamera();
	void camControls(float deltaTime);

protected:
	std::shared_ptr<aie::Renderer2D> m_2dRenderer = nullptr;
	Map* m_map = nullptr;

	Vector2 m_camPos;
	float m_currentPanSpeed = 0;
	const float m_panSpeed = 400;
	const float m_fastPanSpeed = 1000;
	unsigned int m_zoomLevel = 1;

	bool m_zoomInputPressed = false;
};