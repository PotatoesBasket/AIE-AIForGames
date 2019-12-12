#pragma once
#include <random>

class Random
{
public:
	Random() : m_intParams(0, INT_MAX), m_floatParams(0.0f, 1.0f) {}
	Random(unsigned int seed);
	~Random() {}

	/*Set custom seed*/
	void setSeed(unsigned int value) { m_engine.seed(value); }

	/*Returns a random int within a predetermined range (default range is 0 - INT_MAX)*/
	int nextInt();
	/*Sets range of ints that can be returned by nextInt() to given min - max*/
	void setIntRange(int min, int max);
	/*Sets range of ints that can be returned by nextInt() to 0 - INT_MAX*/
	void resetIntRange();

	/*Returns a random float within a predetermined range (default range is 0.0 - 1.0)*/
	float nextFloat();
	/*Sets range of floats that can be returned by nextInt() to given min - max*/
	void setFloatRange(float min, float max);
	/*Sets range of floats that can be returned by nextFloat() to 0.0 - 1.0*/
	void resetFloatRange();

private:
	std::default_random_engine m_engine;

	std::uniform_int_distribution<int> m_intDistribution;
	std::uniform_int_distribution<int>::param_type m_intParams;

	std::uniform_real_distribution<float> m_floatDistribution;
	std::uniform_real_distribution<float>::param_type m_floatParams;
};