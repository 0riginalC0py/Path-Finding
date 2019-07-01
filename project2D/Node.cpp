#include "Node.h"



Node::Node(Vector2 pos, int indexX, int indexY)
{
	m_position = pos;
	m_indexX = indexX;
	m_indexY = indexY;
	m_previous = nullptr;
	m_gScore = 0;
	//Added without instruction
	m_hScore = 0;
	m_fScore = 0;
	m_blocked = false;
	for (int i = 0; i < NEIGHBOUR_COUNT; i++)
	{
		m_pNeighbours[i] = nullptr;
		m_costs[i] = 0;
	}

}


Node::~Node()
{

}


