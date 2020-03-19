#include "Sprite.h"

void Sprite::loadSprite(SpriteInfo sheet)
{
	m_texture = ResourceManager::getInstance().loadTexture(sheet.path);
	m_spriteWidth = sheet.tileWidth;
	m_spriteHeight = sheet.tileHeight;

	if (m_spriteWidth <= 0 || m_spriteHeight <= 0)
		throw new std::exception("invalid sprite size");

	//calculate size of sprite as percentage of total spritesheet
	float cols = m_texture->as<aie::Texture>()->getWidth() / m_spriteWidth;
	float rows = m_texture->as<aie::Texture>()->getHeight() / m_spriteHeight;

	m_percentWidth = 1.0f / cols;
	m_percentHeight = 1.0f / rows;

	m_xPos = m_percentWidth * sheet.colPos;
	m_yPos = m_percentHeight * sheet.rowPos;
}

void Sprite::draw(GameObject* parent, std::shared_ptr<aie::Renderer2D> renderer)
{
	renderer->setUVRect(m_xPos, m_yPos, m_percentWidth, m_percentHeight);

	renderer->drawSpriteTransformed3x3(m_texture->as<aie::Texture>(),
		parent->getGlobalTransformFloat(), m_spriteWidth, m_spriteHeight);

	renderer->setUVRect(1, 1, 1, 1); //reset UV
}