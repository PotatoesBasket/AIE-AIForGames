#pragma once

// 1 animation per spritesheet atm

struct AnimationSheet
{
	char* path = "";
	unsigned int columnCount = 1;
	unsigned int rowCount = 1;
	float animSpeed = 1;
};

const AnimationSheet BUNNY_IDLE;
const AnimationSheet BUNNY_CONSUME;
const AnimationSheet BUNNY_SLEEP;
const AnimationSheet BUNNY_RUN;
const AnimationSheet BUNNY_BREED;
const AnimationSheet BUNNY_DIE;

const AnimationSheet FOX_IDLE;
const AnimationSheet FOX_CONSUME;
const AnimationSheet FOX_SLEEP;
const AnimationSheet FOX_RUN;
const AnimationSheet FOX_BREED;
const AnimationSheet FOX_DIE;

const AnimationSheet GRASS_GROW;
const AnimationSheet GRASS_IDLE;