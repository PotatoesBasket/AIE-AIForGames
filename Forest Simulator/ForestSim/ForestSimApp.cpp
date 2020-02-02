#include "ForestSimApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "ObjectPool.h"

bool ForestSimApp::startup()
{	
	m_2dRenderer = std::make_unique<aie::Renderer2D>();
	m_map = std::make_unique<Map>();
	m_bunnyPool = std::make_unique<ObjectPool>(20);

	//position camera in centre of map
	m_camPos = Vector2(
		(m_map->getMapWidth() - SCR_WIDTH) * 0.5f,
		(m_map->getMapHeight() - SCR_HEIGHT) * 0.5f);

	return true;
}

void ForestSimApp::shutdown()
{
}

void ForestSimApp::update(float deltaTime)
{
	camControls(deltaTime);
}

void ForestSimApp::draw()
{
	clearScreen();
	m_2dRenderer->begin();

	m_map->draw(m_2dRenderer);

	m_2dRenderer->end();
}

void ForestSimApp::camControls(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	// press escape to quit
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	// hold shift to speed up camera panning
	if (input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT) || input->isKeyDown(aie::INPUT_KEY_RIGHT_SHIFT))
		m_currentPanSpeed = m_fastPanSpeed;
	else
		m_currentPanSpeed = m_panSpeed;

	// press space to toggle zoom
	if (input->isKeyDown(aie::INPUT_KEY_SPACE))
		m_zoomInputPressed = true;
	else if (m_zoomInputPressed)
	{
		m_zoomInputPressed = false;

		//set trigger and realign camera
		if (m_zoomedOut)
		{
			m_zoomedOut = false;
			m_camPos.x -= m_map->getTileSize() * 0.5f;
			m_camPos.y -= m_map->getTileSize() * 0.5f;
		}
		else
		{
			m_zoomedOut = true;
			m_camPos.x += m_map->getTileSize() * 0.5f;
			m_camPos.y += m_map->getTileSize() * 0.5f;
		}
	}

	// left/right pan
	if (input->isKeyDown(aie::INPUT_KEY_A) || input->isKeyDown(aie::INPUT_KEY_LEFT))
		m_camPos.x -= m_currentPanSpeed * deltaTime;

	else if (input->isKeyDown(aie::INPUT_KEY_D) || input->isKeyDown(aie::INPUT_KEY_RIGHT))
		m_camPos.x += m_currentPanSpeed * deltaTime;

	// up/down pan
	if (input->isKeyDown(aie::INPUT_KEY_S) || input->isKeyDown(aie::INPUT_KEY_DOWN))
		m_camPos.y -= m_currentPanSpeed * deltaTime;

	else if (input->isKeyDown(aie::INPUT_KEY_W) || input->isKeyDown(aie::INPUT_KEY_UP))
		m_camPos.y += m_currentPanSpeed * deltaTime;

	// update camera zoom
	if (m_zoomedOut == false)
		m_2dRenderer->setCameraScale(1.0f);
	else
		m_2dRenderer->setCameraScale(0.5f);

	// move map boundary slightly depending on zoom level
	float edgeOffset = 0;
	if (m_zoomedOut)
		edgeOffset = 0;
	else
		edgeOffset = m_map->getTileSize() * 0.5f;

	// restrict camera position to map boundaries
	if (m_camPos.x < 0 - edgeOffset)
		m_camPos.x = 0 - edgeOffset;
	if (m_camPos.x > m_map->getMapWidth() - SCR_WIDTH - edgeOffset)
		m_camPos.x = m_map->getMapWidth() - SCR_WIDTH - edgeOffset;
	if (m_camPos.y < 0 - edgeOffset)
		m_camPos.y = 0 - edgeOffset;
	if (m_camPos.y > m_map->getMapHeight() - SCR_HEIGHT - edgeOffset)
		m_camPos.y = m_map->getMapHeight() - SCR_HEIGHT - edgeOffset;

	// update camera pos
	m_2dRenderer->setCameraPos(m_camPos.x, m_camPos.y);
}