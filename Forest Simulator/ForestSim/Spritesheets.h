#pragma once

// static individual sprites on a sheet of many

struct Spritesheet
{
	char* path = "";
	unsigned int width = 0;
	unsigned int height = 0;
	unsigned int colPos = 0; //position on sheet
	unsigned int rowPos = 0;
};