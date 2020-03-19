#pragma once
#include "GameObject.h"
#include "ResourceManager.h"
#include "SpriteInfo.h"
#include <Texture.h>

class Sprite : public Component
{
public:
	Sprite(SpriteInfo sheet) { loadSprite(sheet); }
	~Sprite() {}

	//load spritesheet and init values, also use to switch out sheets
	void loadSprite(SpriteInfo sheet);

private:
	void draw(GameObject* parent, std::shared_ptr<aie::Renderer2D> renderer) override;

protected:
	std::shared_ptr<ResourceBase> m_texture = nullptr;

	//sprite info
	unsigned int m_spriteWidth = 0;
	unsigned int m_spriteHeight = 0;

	//sprite on spritesheet as percentages for setting UV Rect
	float m_xPos = 0;
	float m_yPos = 0;
	float m_percentWidth = 0;
	float m_percentHeight = 0;
};