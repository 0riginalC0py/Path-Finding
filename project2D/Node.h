#pragma once
#include "Vector2.h"
//4 or 8(diagnolas included)
#define NEIGHBOUR_COUNT 8

struct Node
{


	Node(Vector2 pos, int indexX, int indexY);
	~Node();

	int m_indexX;
	int m_indexY;



	Vector2 m_position;
	Node* m_previous;
	float m_gScore;
	float m_hScore;
	float m_fScore;

	

	Node* m_pNeighbours[NEIGHBOUR_COUNT];


	bool m_blocked;
	float m_costs[NEIGHBOUR_COUNT];
};

