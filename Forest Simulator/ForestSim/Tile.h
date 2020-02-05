#pragma once
#include "GameObject.h"

class Sprite;

class Tile : public GameObject
{
public:
	enum Type
	{
		grass,
		water,
		tree,
		rock
	};
	
	Tile(Type type, Vector2 position) : m_type(type) { setPosition(position); }
	~Tile() {}

	Type const getType() { return m_type; }

private:
	Type m_type;
};