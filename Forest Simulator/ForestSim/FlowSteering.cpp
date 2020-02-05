#include "FlowSteering.h"
#include "GameObject.h"
#include "FlowField.h"

Vector2 FlowSteering::getForce(GameObject* object) const
{
	if (m_flowField == nullptr)
		return Vector2(0, 0);

	//keep from going offscreen
	if (object->getPosition().x < 0)
		object->setPosition(Vector2(0, object->getPosition().y));

	if (object->getPosition().x > m_cols * m_cellSize)
		object->setPosition(Vector2(m_cols * m_cellSize - 1, object->getPosition().y));

	if (object->getPosition().y < 0)
		object->setPosition(Vector2(object->getPosition().x, 0));

	if (object->getPosition().y > m_rows * m_cellSize)
		object->setPosition(Vector2(object->getPosition().x, m_rows * m_cellSize - 1));

	//get current cell
	unsigned int ix = int(object->getPosition().x / m_cellSize);
	unsigned int iy = int(object->getPosition().y / m_cellSize);

	unsigned int index = iy * m_cols + ix;

	return Vector2(
		m_flowField[index].x * object->getMaxForce(),
		m_flowField[index].y * object->getMaxForce());
}

void FlowSteering::setFlowField(FlowField* flowField)
{
	m_flowField = flowField->getFlowField();
	m_rows = flowField->ROWS;
	m_cols = flowField->COLS;
	m_cellSize = flowField->CELLSIZE;
}