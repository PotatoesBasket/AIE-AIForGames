#pragma once
#include "ISteering.h"
#include "FlowField.h"

class FlowField;

class FlowSteering : public ISteering
{
public:
	Vector2 getForce(GameObject* object) const override;

	void setFlowField(FlowField* flowField);

protected:
	int m_rows = 0;
	int m_cols = 0;
	float m_cellSize = 0;
	Vector2* m_flowField = nullptr;
};