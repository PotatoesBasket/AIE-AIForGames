#pragma once
#include "GameObject.h"
#include "ResourceManager.h"
#include "AnimationSheets.h"
#include <Texture.h>

class AnimatedSprite : public Component
{
public:
	AnimatedSprite(AnimationSheet sheet);
	~AnimatedSprite() {}

	//load spritesheet and init values, also use to switch out sheets
	void loadAnim(AnimationSheet sheet);

private:
	void update(GameObject* parent, float deltaTime) override;
	void draw(GameObject* parent, aie::Renderer2D* renderer) override;

	//update current portion of spritesheet being renderered
	void updateUVRect(aie::Renderer2D* renderer);

protected:
	std::shared_ptr<ResourceBase> m_texture = nullptr;

	//animation info
	float m_animSpeed = 1;
	float m_timer = 0;
	unsigned int m_currentCol = 0;
	unsigned int m_currentRow = 0;

	//sprite info
	unsigned int m_spriteWidth = 0;
	unsigned int m_spriteHeight = 0;

	//sheet info
	unsigned int m_columnCount = 1;
	unsigned int m_rowCount = 1;
};