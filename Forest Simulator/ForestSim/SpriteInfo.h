#pragma once

struct SpriteInfo
{
	const char* path = "";
	unsigned int tileWidth = 0;
	unsigned int tileHeight = 0;
	unsigned int colPos = 0;
	unsigned int rowPos = 0;
};

const SpriteInfo grassLow =		{ "../bin/textures/grass_72px.png", 72, 72, 0, 0 };
const SpriteInfo grassHigh =	{ "../bin/textures/grass_72px.png", 72, 72, 1, 0 };
const SpriteInfo freshWater =	{ "../bin/textures/water_72px.png", 72, 72, 0, 0 };