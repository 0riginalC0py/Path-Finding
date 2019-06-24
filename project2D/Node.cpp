#include "Node.h"



Node::Node(Vector2 v2Pos, int nIndexX, int nIndexY)
{
	m_v2Position = v2Pos;
	m_nIndexX = nIndexX;
	m_nIndexY = nIndexY;

	m_pPrevious = nullptr;
	m_nGScore = 0;
	m_nHScore = 0;
	m_nFScore = 0;
	m_bBlocked = false;
	
	for (int i = 0; i < NEIGHBOUR_COUNT; i++)
	{
		m_apNeighbours[i] = nullptr;
		m_anCosts[i] = 0;
	}
}


Node::~Node()
{
}
