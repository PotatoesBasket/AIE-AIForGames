#include "RNG.h"
#include <math.h>

int RNG::nextInt()
{
	return m_intDistribution(m_engine);
}

void RNG::setIntRange(int min, int max)
{
	m_intParams._Min = min;
	m_intParams._Max = max;
	m_intDistribution.param(m_intParams);
}

void RNG::resetIntRange()
{
	m_intParams._Min = 0;
	m_intParams._Max = INT_MAX;
	m_intDistribution.param(m_intParams);
}

float RNG::nextFloat()
{
	return m_floatDistribution(m_engine);
}

void RNG::setFloatRange(float min, float max)
{
	m_floatParams._Min = min;
	m_floatParams._Max = max;
	m_floatDistribution.param(m_floatParams);
}

void RNG::resetFloatRange()
{
	m_floatParams._Min = 0.0f;
	m_floatParams._Max = 1.0f;
	m_floatDistribution.param(m_floatParams);
}