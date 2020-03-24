#pragma once
#include "Composite.h"

//OR node for running a list of behaviours consecutively until one succeeds
class Selector : public Composite
{
public:
	Selector() { m_continueResult = FAILURE; }
	~Selector() {}
};