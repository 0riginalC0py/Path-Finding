#include "Grid.h"
#include "Node.h"
#include "Vector2.h"
#include <search.h>
#include <cmath>
#include "DebugList.h"
#include "BB.h"
#include <fstream>





Grid::Grid(int sizeWidth, int sizeHeight)
{
	m_Height = sizeHeight;
	m_Width = sizeWidth;
	//Allocate 2d array of pointers
	m_NodeList = new Node**[m_Height];
	for (int i = 0; i < m_Width; i++)
	{
		m_NodeList[i] = new Node*[m_Width];
	}
	//Allocate nodes
	for (int x = 0; x < m_Height; x++)
	{
		for (int y = 0; y < m_Width; y++)
		{
			Vector2 pos;
			pos.m_x = x * SQUARE_SIZE + GRID_OFFSET_POSX;
			pos.m_y = y * SQUARE_SIZE + GRID_OFSSET_POSY;
			m_NodeList[x][y] = new Node(pos, x, y);
		}
	}
	//Connect Nodes to neighbours
	//|7|2|6|
	//|1|C|3|
	//|4|0|5|
		for (int x = 0; x < m_Height; x++)
	{
		for (int y = 0; y < m_Width; y++)
		{
			if (y > 0)
				m_NodeList[x][y]->m_pNeighbours[0] = m_NodeList[x][y - 1];
			if (x > 0)
				m_NodeList[x][y]->m_pNeighbours[1] = m_NodeList[x - 1][y];
			if (y < m_Height - 1)
				m_NodeList[x][y]->m_pNeighbours[2] = m_NodeList[x][y + 1];
			if (x < m_Width - 1)
				m_NodeList[x][y]->m_pNeighbours[3] = m_NodeList[x + 1][y];
			if (y > 0 && x > 0)
				m_NodeList[x][y]->m_pNeighbours[4] = m_NodeList[x - 1][y - 1];
			if (y > 0 && x < m_Width - 1)
				m_NodeList[x][y]->m_pNeighbours[5] = m_NodeList[x + 1][y - 1];
			if (y < m_Height - 1 && x < m_Width - 1)
				m_NodeList[x][y]->m_pNeighbours[6] = m_NodeList[x + 1][y + 1];
			if (y < m_Height - 1 && x > 0)
				m_NodeList[x][y]->m_pNeighbours[7] = m_NodeList[x - 1][y + 1];


			m_NodeList[x][y]->m_costs[0] = STRAIGHT_DOWN;
			m_NodeList[x][y]->m_costs[1] = STRAIGHT_LEFT;
			m_NodeList[x][y]->m_costs[2] = STRAIGHT_UP;
			m_NodeList[x][y]->m_costs[3] = STRAIGHT_RIGHT;
			m_NodeList[x][y]->m_costs[4] = DIAGNOL_DOWN_LEFT;
			m_NodeList[x][y]->m_costs[5] = DIAGNOL_DOWN_RIGHT;
			m_NodeList[x][y]->m_costs[6] = DIAGNOL_UP_RIGHT;
			m_NodeList[x][y]->m_costs[7] = DIAGNOL_UP_LEFT;
		}
	}
		//Create closed list
		m_ClosedList = new bool[m_Width * m_Height];

}


Grid::~Grid()
{
	for (int x = 0; x < m_Height; x++)
	{
		for (int y = 0; y < m_Width; y++)
		{
			delete m_NodeList[x][y];
			m_NodeList[x][y] = nullptr;
		}
	}
	for (int i = 0; i < m_Width; i++)
	{
		delete[] m_NodeList[i];
		m_NodeList[i] = nullptr;
	}
	delete[] m_NodeList;
	m_NodeList = nullptr;
	delete m_ClosedList;
	m_ClosedList = nullptr;
}
//----------------------------------------------------
//Draws lines and boxes of grid.
//Consider turning on/off via key press.
//----------------------------------------------------
void Grid::Draw(aie::Renderer2D* renderer, BB levelManager)
{
		
		//Draw Boxes/Lines loop.
	for (int x = 0; x < m_Height; x++)
	{
		for (int y = 0; y < m_Width; y++)
		{
			Vector2 pos = m_NodeList[x][y]->m_position;
			//----------------------------------------------------
			//If no longer wanting to draw boxes comment
			//out from here.
			//----------------------------------------------------
			if (levelManager.m_debugList.item[0])
			{
				renderer->SetRenderColour(0, 1.0f, 1.0f, 0.3f);
				if (m_NodeList[x][y]->m_blocked)
					renderer->SetRenderColour(1.0f, 0, 0);
				renderer->DrawBox(pos.m_x, pos.m_y, SQUARE_SIZE - SQUARE_GAP_BETWEEN, SQUARE_SIZE - SQUARE_GAP_BETWEEN);
			}
			//----------------------------------------------------
			//Draw box end here
			//----------------------------------------------------

			//----------------------------------------------------
			//If no longer wanting to draw lines comment
			//out from here.
			//----------------------------------------------------
			if (levelManager.m_debugList.item[1])
			{
				for (int n = 0; n < NEIGHBOUR_COUNT; n++)
				{
					if (m_NodeList[x][y]->m_pNeighbours[n])
					{
						Vector2 Neighbour = m_NodeList[x][y]->m_pNeighbours[n]->m_position;
						renderer->SetRenderColour(1.0f, 0, 1.0f);
						renderer->DrawLine(pos.m_x, pos.m_y, Neighbour.m_x, Neighbour.m_y);
					}
				}
			}
			//----------------------------------------------------
			//Draw line end here
			//----------------------------------------------------

			renderer->SetRenderColour(1.0f, 1.0f, 1.0f);
		}
	}
}

Node* Grid::GetNodeByPos(Vector2 pos)
{
	int x = (int)((pos.m_x - GRID_OFFSET_POSX + (SQUARE_SIZE * 0.5f)) / SQUARE_SIZE);
	int y = (int)((pos.m_y - GRID_OFSSET_POSY + (SQUARE_SIZE * 0.5f)) / SQUARE_SIZE);
	if (x < 0 || y < 0 || x >= m_Width || y >= m_Height)
		return nullptr;
	return m_NodeList[x][y];
}

//void Grid::SortOpenList()
//{
//	for (int i = 0; i < m_OpenList.size() - 1; i++)
//	{
//		for (int j = 0; j < m_OpenList.size() - 1 - i; j++)
//		{
//			if (m_OpenList[j]->m_fScore < m_OpenList[j + 1]->m_fScore)
//			{
//				Node* t = m_OpenList[j];
//				m_OpenList[j] = m_OpenList[j + 1];
//				m_OpenList[j + 1] = t;
//			}
//		}
//	}
//}



bool Grid::FindPath(Vector2 start, Vector2 end, std::vector<Vector2>& path)
{
	Node* startNode = GetNodeByPos(start);
	Node* endNode = GetNodeByPos(end);
	if (!startNode || !endNode)
		return false;
	if (startNode == endNode)
		return false;
	if (startNode->m_blocked || endNode->m_blocked)
		return false;

	//initilisation
	path.clear();
	m_OpenList.Clear();
	bool foundpath = false;
	memset(m_ClosedList, 0, sizeof(bool) * m_Width *m_Height);

	startNode->m_previous = nullptr;
	startNode->m_gScore = 0;
	//Needs to know how far away it is from node?
	startNode->m_hScore = FindEnd(startNode, endNode);
	//Needs an f score
	startNode->m_fScore = startNode->m_gScore + startNode->m_hScore;
	m_OpenList.Push(startNode);

	//algorithm
	while (m_OpenList.GetCount() > 0)
	{

		
		Node* current = m_OpenList.Pop();
		

		//add to closed list.
		int index = current->m_indexY * m_Width + current->m_indexX;
		m_ClosedList[index] = true;
		if (current == endNode)
		{
			foundpath = true;
			break;
		}
		//
		for (int i = 0; i < NEIGHBOUR_COUNT; i++)
		{
			Node* neighbour = current->m_pNeighbours[i];
			if (!neighbour)
				continue;

			if (neighbour->m_blocked)
				continue;

			int nIndex = neighbour->m_indexY * m_Width + neighbour->m_indexX;
			if (m_ClosedList[nIndex])
				continue;

			if (!m_OpenList.FindNode(neighbour))
			{
				neighbour->m_previous = current;
				neighbour->m_gScore = current->m_gScore + current->m_costs[i];
				neighbour->m_hScore = FindEnd(neighbour, endNode);
				neighbour->m_fScore = neighbour->m_gScore + neighbour->m_hScore;
				m_OpenList.Push(neighbour);
			}
			//Checks if better path
			else
			{
				float nCost = current->m_fScore + current->m_costs[i];
				if (nCost < neighbour->m_fScore)
				{
					neighbour->m_gScore = nCost;
					neighbour->m_fScore = neighbour->m_gScore + neighbour->m_hScore;
					neighbour->m_previous = current;

				}
			}
		}
	}
	if (foundpath)
	{
		Node* current = endNode;
		while (current)
		{
			path.insert(path.begin(), current->m_position);
			current = current->m_previous;
		}
		return true;
	}
	return false;
}

//----------------------------------------------------
//Finds the 'h' score for the node based on where it is
//and the distance to the end.
//----------------------------------------------------
float Grid::FindEnd(Node* current, Node* end)
{
	
	int distantx = abs(current->m_indexX - end->m_indexX);
	int distanty = abs(current->m_indexY - end->m_indexY);

	if (distantx > distanty)
		return (DIAGNOLS * distanty) + STRAIGHTS * (distantx - distanty) * INADMISSIBLE_HEUR;
	else
		return (DIAGNOLS * distantx) + STRAIGHTS * (distanty - distantx) * INADMISSIBLE_HEUR;
}


void Grid::Save()
{
	//Get the current grids state.
	//If more than 2 states (eg enums)
	//change 'saved' array type.
	bool saved[GRID_WIDTH * GRID_HEIGHT];
	for (int i = 0; i < GRID_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_WIDTH; j++)
			saved[(i * 10) + j] = m_NodeList[i][j]->m_blocked;
	}
	std::fstream file;
	//Open or create file.
	file.open("level.dat", std::ios::out);
	file.close();
	file.open("level.dat", std::ios::out | std::ios::binary);
	//Write to file.
	file.write((char*)&saved, sizeof(bool[GRID_WIDTH * GRID_HEIGHT]));
	//Close file.
	file.close();
}

void Grid::Load()
{
	bool load[GRID_WIDTH * GRID_HEIGHT];
	std::fstream file;
	//Open or check if file exists.
	file.open("level.dat", std::ios::in | std::ios::binary);
	//Display error if nothing to load.

	//Read from file.
	file.read((char*)&load, sizeof(bool[GRID_WIDTH * GRID_HEIGHT]));
	//Close file.
	file.close();
	for (int i = 0; i < GRID_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_WIDTH; j++)
			m_NodeList[i][j]->m_blocked = load[(i * 10) + j];
	}
}