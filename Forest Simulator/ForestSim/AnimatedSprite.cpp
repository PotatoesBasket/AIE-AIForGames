#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(AnimationSheet sheet)
{
	loadAnim(sheet);
}

void AnimatedSprite::loadAnim(AnimationSheet sheet)
{
	m_texture = ResourceManager::getInstance().loadTexture(sheet.path);
	m_columnCount = sheet.columnCount;
	m_rowCount = sheet.rowCount;
	m_animSpeed = sheet.animSpeed;

	m_spriteWidth = m_texture->as<aie::Texture>()->getWidth() / m_columnCount;
	m_spriteHeight = m_texture->as<aie::Texture>()->getHeight() / m_rowCount;
}

void AnimatedSprite::update(GameObject* parent, float deltaTime)
{
	m_timer += deltaTime;
}

void AnimatedSprite::draw(GameObject* parent, std::shared_ptr<aie::Renderer2D> renderer)
{
	updateUVRect(renderer);

	renderer->drawSpriteTransformed3x3(m_texture->as<aie::Texture>(),
		parent->getGlobalTransformFloat(), m_spriteWidth, m_spriteHeight);

	renderer->setUVRect(1, 1, 1, 1); //reset UV
}

void AnimatedSprite::updateUVRect(std::shared_ptr<aie::Renderer2D> renderer)
{
	//get size of single frame as percentage of total spritesheet
	float width = 1.0f / m_columnCount;
	float height = 1.0f / m_rowCount;

	//initialise
	renderer->setUVRect(width * m_currentCol, height * m_currentRow, width, height);

	//play animation
	if (m_timer > m_animSpeed)
	{
		++m_currentCol;

		if (m_currentCol == m_columnCount)
		{
			++m_currentRow;
			m_currentCol = 0;
		}

		if (m_currentRow == m_rowCount)
			m_currentRow = 0;

		renderer->setUVRect(width * m_currentCol, height * m_currentRow, width, height);

		m_timer = 0;
	}
}