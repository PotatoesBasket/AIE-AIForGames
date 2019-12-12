#include "ForestSimApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"

bool ForestSimApp::startup()
{	
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	return true;
}

void ForestSimApp::shutdown()
{
	delete m_font;
	delete m_2dRenderer;
}

void ForestSimApp::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void ForestSimApp::draw()
{
	clearScreen();
	m_2dRenderer->begin();

	m_2dRenderer->end();
}