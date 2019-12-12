#include "Random.h"
#include <math.h>

Random::Random(unsigned int seed) : m_intParams(0, INT_MAX), m_floatParams(0.0f, 1.0f)
{
	setSeed(seed);
}

int Random::nextInt()
{
	return m_intDistribution(m_engine);
}

void Random::setIntRange(int min, int max)
{
	m_intParams._Min = min;
	m_intParams._Max = max;
	m_intDistribution.param(m_intParams);
}

void Random::resetIntRange()
{
	m_intParams._Min = 0;
	m_intParams._Max = INT_MAX;
	m_intDistribution.param(m_intParams);
}

float Random::nextFloat()
{
	return m_floatDistribution(m_engine);
}

void Random::setFloatRange(float min, float max)
{
	m_floatParams._Min = min;
	m_floatParams._Max = max;
	m_floatDistribution.param(m_floatParams);
}

void Random::resetFloatRange()
{
	m_floatParams._Min = 0.0f;
	m_floatParams._Max = 1.0f;
	m_floatDistribution.param(m_floatParams);
}