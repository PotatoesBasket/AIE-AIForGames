#pragma once

//stats are a range from 0 (min) to 100 (max)
//all animal stats start at 0
//usually, reaching 100 means they ded
//set percentage stat rises naturally every "second"

struct Stat
{
	Stat() {}
	Stat(float incrementPercent) : m_inc(incrementPercent) {}

	float m_min = 0, m_max = 100, m_current = 0, m_inc = 0;
};