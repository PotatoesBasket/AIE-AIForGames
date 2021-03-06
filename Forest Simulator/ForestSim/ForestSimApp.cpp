#include "ForestSimApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "ScreenDefines.h"
#include <time.h>

bool ForestSimApp::startup()
{
	RNG& rng = RNG::getInstance();
	rng.setSeed((int)time);

	m_2dRenderer = std::make_unique<aie::Renderer2D>();
	m_map = std::make_unique<Map>();
	
	initCamera();

	return true;
}

void ForestSimApp::update(float deltaTime)
{
	camControls(cappedDeltaTime(deltaTime));
	m_map->update(cappedDeltaTime(deltaTime));

	m_debug.getInput();
	m_debug.printData();
}

void ForestSimApp::draw()
{
	clearScreen();

	m_2dRenderer->begin();

	m_map->draw(m_2dRenderer.get());

	m_2dRenderer->end();
}

void ForestSimApp::initCamera()
{
	// init cam pan speed
	m_currentPanSpeed = m_panSpeed;

	// position camera in centre of map
	m_camPos = glm::vec2(
		(m_map->getMapWidthPx() - SCR_WIDTH) * 0.5f,
		(m_map->getMapHeightPx() - SCR_HEIGHT) * 0.5f);

	// set initial camera scale to medium zoom
	m_2dRenderer->setCameraScale(1.5f);
}

void ForestSimApp::camControls(float deltaTime)
{
	aie::Input* getInput = aie::Input::getInstance();

	// press escape to quit
	if (getInput->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	//// press space to toggle zoom
	//if (getInput->isKeyDown(aie::INPUT_KEY_SPACE))
	//	m_zoomInputPressed = true;
	//else if (m_zoomInputPressed)
	//{
	//	m_zoomInputPressed = false;

	//	// set zoom and realign camera
	//	switch (m_zoomLevel)
	//	{
	//	case 0:
	//		m_2dRenderer->setCameraScale(1.0f);
	//		++m_zoomLevel;
	//		break;
	//	case 1:
	//		m_2dRenderer->setCameraScale(1.5f);
	//		++m_zoomLevel;
	//		break;
	//	case 2:
	//		m_2dRenderer->setCameraScale(0.5f);
	//		m_zoomLevel = 0;
	//	}
	//}

	// left/right pan
	if (getInput->isKeyDown(aie::INPUT_KEY_A) || getInput->isKeyDown(aie::INPUT_KEY_LEFT))
		m_camPos.x -= m_currentPanSpeed * deltaTime;

	else if (getInput->isKeyDown(aie::INPUT_KEY_D) || getInput->isKeyDown(aie::INPUT_KEY_RIGHT))
		m_camPos.x += m_currentPanSpeed * deltaTime;

	// up/down pan
	if (getInput->isKeyDown(aie::INPUT_KEY_S) || getInput->isKeyDown(aie::INPUT_KEY_DOWN))
		m_camPos.y -= m_currentPanSpeed * deltaTime;

	else if (getInput->isKeyDown(aie::INPUT_KEY_W) || getInput->isKeyDown(aie::INPUT_KEY_UP))
		m_camPos.y += m_currentPanSpeed * deltaTime;

	// hold shift to speed up camera panning
	if (getInput->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT) || getInput->isKeyDown(aie::INPUT_KEY_RIGHT_SHIFT))
		m_currentPanSpeed = m_fastPanSpeed * m_2dRenderer->getCameraScale();
	else
		m_currentPanSpeed = m_panSpeed * m_2dRenderer->getCameraScale();

	// restrict camera position to map boundaries
	// its weird and i hate it
	float halfTileSize = m_map->getTileSize() * 0.5f;

	switch (m_zoomLevel)
	{
	case 0:
		if (m_camPos.x < 0.0f - SCR_WIDTH * 0.25f - halfTileSize)
			m_camPos.x = 0.0f - SCR_WIDTH * 0.25f - halfTileSize;
		if (m_camPos.x > m_map->getMapWidthPx() - SCR_WIDTH * 0.75f - halfTileSize)
			m_camPos.x = m_map->getMapWidthPx() - SCR_WIDTH * 0.75f - halfTileSize;
		if (m_camPos.y < 0.0f - SCR_HEIGHT * 0.25f + halfTileSize)
			m_camPos.y = 0.0f - SCR_HEIGHT * 0.25f + halfTileSize;
		if (m_camPos.y > m_map->getMapHeightPx() - SCR_HEIGHT * 0.75f + halfTileSize)
			m_camPos.y = m_map->getMapHeightPx() - SCR_HEIGHT * 0.75f + halfTileSize;
		break;

	case 1:
		if (m_camPos.x < 0.0f - halfTileSize)
			m_camPos.x = 0.0f - halfTileSize;
		if (m_camPos.x > m_map->getMapWidthPx() - SCR_WIDTH - halfTileSize)
			m_camPos.x = m_map->getMapWidthPx() - SCR_WIDTH - halfTileSize;
		if (m_camPos.y < 0.0f + halfTileSize)
			m_camPos.y = 0.0f + halfTileSize;
		if (m_camPos.y > m_map->getMapHeightPx() - SCR_HEIGHT + halfTileSize)
			m_camPos.y = m_map->getMapHeightPx() - SCR_HEIGHT + halfTileSize;
		break;

	case 2:
		if (m_camPos.x < 0.0f + SCR_WIDTH * 0.25f - halfTileSize)
			m_camPos.x = 0.0f + SCR_WIDTH * 0.25f - halfTileSize;
		if (m_camPos.x > m_map->getMapWidthPx() - SCR_WIDTH * 1.25f - halfTileSize)
			m_camPos.x = m_map->getMapWidthPx() - SCR_WIDTH * 1.25f - halfTileSize;
		if (m_camPos.y < 0.0f + SCR_HEIGHT * 0.25f + halfTileSize)
			m_camPos.y = 0.0f + SCR_HEIGHT * 0.25f + halfTileSize;
		if (m_camPos.y > m_map->getMapHeightPx() - SCR_HEIGHT * 1.25f + halfTileSize)
			m_camPos.y = m_map->getMapHeightPx() - SCR_HEIGHT * 1.25f + halfTileSize;
		break;
	}

	// update camera pos
	m_2dRenderer->setCameraPos(m_camPos.x, m_camPos.y);
}