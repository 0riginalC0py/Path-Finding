#include "Grid.h"
#include "Node.h"
#include "Vector2.h"
#include "Font.h"
#include "Application.h"
#include <algorithm>
#include <cmath>
#include <fstream>



Grid::Grid(int nWidth, int nHeight, DebugList* pDebugList)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_font = new aie::Font("./font/consolas.ttf", 10);

	//Allocate 2D array of pointers that will be used to store nodes
	m_apNodeList = new Node**[m_nWidth];
	for (int i = 0; i < m_nWidth; i++)
	{
		m_apNodeList[i] = new Node*[m_nHeight];
	}

	//Allocate Nodes
	for (int x = 0; x < m_nWidth; x++)
	{
		for (int y = 0; y < m_nHeight; y++)
		{
			Vector2 pos;
			pos.x = x * SQUARE_SIZE + GRID_POS_X;
			pos.y = y * SQUARE_SIZE + GRID_POS_Y;

			m_apNodeList[x][y] = new Node(pos, x, y);
		}
	}

	//Connect the Nodes to their neighbours
	// |7|2|6|
	// |1|C|3|
	// |4|0|5|
	for (int x = 0; x < m_nWidth; x++)
	{
		for (int y = 0; y < m_nHeight; y++)
		{
			if(y > 0)
			m_apNodeList[x][y]->m_apNeighbours[0] = m_apNodeList[x][y - 1];

			if (x > 0)
				m_apNodeList[x][y]->m_apNeighbours[1] = m_apNodeList[x - 1][y];

			if (y < m_nHeight - 1)
				m_apNodeList[x][y]->m_apNeighbours[2] = m_apNodeList[x][y + 1];

			if (x < m_nWidth - 1)
				m_apNodeList[x][y]->m_apNeighbours[3] = m_apNodeList[x + 1][y];

			if(y > 0 && x > 0)
				m_apNodeList[x][y]->m_apNeighbours[4] = m_apNodeList[x - 1][y - 1];

			if (y > 0 && x < m_nWidth - 1)
				m_apNodeList[x][y]->m_apNeighbours[5] = m_apNodeList[x + 1][y - 1];

			if (y < m_nHeight - 1 && x < m_nWidth - 1)
				m_apNodeList[x][y]->m_apNeighbours[6] = m_apNodeList[x + 1][y + 1];

			if (y < m_nHeight - 1 && x > 0)
				m_apNodeList[x][y]->m_apNeighbours[7] = m_apNodeList[x - 1][y + 1];

			m_apNodeList[x][y]->m_anCosts[0] = ADJACENT_COST;
			m_apNodeList[x][y]->m_anCosts[1] = ADJACENT_COST;
			m_apNodeList[x][y]->m_anCosts[2] = ADJACENT_COST;
			m_apNodeList[x][y]->m_anCosts[3] = ADJACENT_COST;
			m_apNodeList[x][y]->m_anCosts[4] = DIAGONAL_COST;
			m_apNodeList[x][y]->m_anCosts[5] = DIAGONAL_COST;
			m_apNodeList[x][y]->m_anCosts[6] = DIAGONAL_COST;
			m_apNodeList[x][y]->m_anCosts[7] = DIAGONAL_COST;
		}
	}

	//Create the closed list
	m_bClosedList = new bool[m_nWidth * m_nHeight];

	m_pDebug = pDebugList;
}


Grid::~Grid()
{
	for (int x = 0; x < m_nWidth; x++)
	{
		for (int y = 0; y < m_nHeight; y++)
		{
			delete m_apNodeList[x][y];
		}
		delete[] m_apNodeList[x];
	}
	delete[] m_apNodeList;

	delete m_bClosedList;

	delete m_font;
}

void Grid::Draw(aie::Renderer2D * pRenderer)
{
	for (int x = 0; x < m_nWidth; x++)
	{
		for (int y = 0; y < m_nHeight; y++)
		{
			Vector2 v2Pos = m_apNodeList[x][y]->m_v2Position;

			pRenderer->SetRenderColour(0x5F118C20);
			if (m_apNodeList[x][y]->m_bBlocked)
				pRenderer->SetRenderColour(0x0F8EDCFF);

			if (m_apNodeList)
				pRenderer->DrawBox(v2Pos.x, v2Pos.y, SQUARE_SIZE, SQUARE_SIZE);

			for (int n = 0; n < NEIGHBOUR_COUNT; n++)
			{
				if (m_apNodeList[x][y]->m_apNeighbours[n])
				{
						if (m_pDebug->item[2])
						{
							Vector2 v2NeighbourPos = m_apNodeList[x][y]->m_apNeighbours[n]->m_v2Position;
							pRenderer->SetRenderColour(0x9698DB10);
							pRenderer->DrawLine(v2Pos.x, v2Pos.y, v2NeighbourPos.x, v2NeighbourPos.y);
							if (!m_apNodeList[x][y]->m_apNeighbours[n]->m_bBlocked)
							{
								if (m_pDebug->item[3])
								{
									char HScore[32];
									sprintf_s(HScore, 32, "HS: %i", m_apNodeList[x][y]->m_apNeighbours[n]->m_nHScore);
									pRenderer->SetRenderColour(0x25FB64FF);
									pRenderer->DrawText2D(m_font, HScore, v2NeighbourPos.x - 25, v2NeighbourPos.y + 15);
									char GScore[32];
									sprintf_s(GScore, 32, "GS: %i", m_apNodeList[x][y]->m_apNeighbours[n]->m_nGScore);
									pRenderer->SetRenderColour(0x25FB64FF);
									pRenderer->DrawText2D(m_font, GScore, v2NeighbourPos.x - 25, v2NeighbourPos.y);
									char FScore[32];
									sprintf_s(FScore, 32, "FS: %i", m_apNodeList[x][y]->m_apNeighbours[n]->m_nFScore);
									pRenderer->SetRenderColour(0x25FB64FF);
									pRenderer->DrawText2D(m_font, FScore, v2NeighbourPos.x - 25, v2NeighbourPos.y - 15);
								}
							}
						}
					}
				}
			}
			pRenderer->SetRenderColour(0xFFFFFFFF);
		}
	}

Node* Grid::GetNodeByPosition(Vector2 v2Pos)
{
	int x = (int)((v2Pos.x - GRID_POS_X + (SQUARE_SIZE * 0.5f)) / SQUARE_SIZE);
	int y = (int)((v2Pos.y - GRID_POS_Y + (SQUARE_SIZE * 0.5f)) / SQUARE_SIZE);

	if (x < 0 || y < 0 || x >= m_nWidth || y >= m_nHeight)
		return nullptr;
	return m_apNodeList[x][y];
}

//void Grid::SortOpenList()
//{
//	for (int i = 0; i < m_OpenList.size(); i++)
//	{
//		for (int j = 0; j < m_OpenList.size() - 1 - i; j++)
//		{
//			if (m_OpenList[j]->m_nGScore < m_OpenList[j + 1]->m_nGScore)
//			{
//				Node* pSwap = m_OpenList[j];
//				m_OpenList[j] = m_OpenList[j + 1];
//				m_OpenList[j + 1] = pSwap;
//			}
//		}
//	}
//}

bool Grid::FindPath(Vector2 v2Start, Vector2 v2End, std::vector<Vector2>& path)
{
	//Find start and end nodes
	Node* pStartNode = GetNodeByPosition(v2Start);
	Node* pEndNode = GetNodeByPosition(v2End);
	path.clear();

	if (!pStartNode || !pEndNode)
		return false;

	if (pStartNode == pEndNode)
		return false;

	if (pStartNode->m_bBlocked || pEndNode->m_bBlocked)
		return false;

	//Initialization
	m_OpenList.Clear();
	memset(m_bClosedList, 0, sizeof(bool) * m_nWidth * m_nHeight);
	bool bFoundPath = false;

	pStartNode->m_pPrevious = nullptr;
	pStartNode->m_nGScore = 0;
 	pStartNode->m_nHScore = CalculateHeuristic(pStartNode, pEndNode);
	pStartNode->m_nFScore = pStartNode->m_nGScore + pStartNode->m_nHScore;
	
	m_OpenList.Push(pStartNode);

	//The Algorithm
	while (m_OpenList.GetCount() > 0)
	{
		//SortOpenList();

		Node* pCurrent = m_OpenList.Pop();

		//Add to closed list
		int nIndex = pCurrent->m_nIndexY * m_nWidth + pCurrent->m_nIndexX;
		m_bClosedList[nIndex] = true;
		
		if (pCurrent == pEndNode)
		{
			bFoundPath = true;
			break;
		}

		for (int i = 0; i < NEIGHBOUR_COUNT; i++)
		{
			Node* pNeighbour = pCurrent->m_apNeighbours[i];
			
			if (!pNeighbour)
				continue;

			if (pNeighbour->m_bBlocked)
				continue;

			int nNeighbourIndex = pNeighbour->m_nIndexY * m_nWidth + pNeighbour->m_nIndexX;
			if (m_bClosedList[nNeighbourIndex])
				continue;

			//Not in open List
			if(!m_OpenList.Find(pNeighbour))
			{
			pNeighbour->m_pPrevious = pCurrent;
			pNeighbour->m_nGScore = pCurrent->m_nGScore + pCurrent->m_anCosts[i];
			pNeighbour->m_nHScore = CalculateHeuristic(pNeighbour, pEndNode);
			pNeighbour->m_nFScore = pNeighbour->m_nGScore + pNeighbour->m_nHScore;

			m_OpenList.Push(pNeighbour);
			}
			else
			{
				//Is in open lsit, check if this is cheaper
				int nCost = pCurrent->m_nGScore + pCurrent->m_anCosts[i] + pNeighbour->m_nHScore;
				if (nCost < pNeighbour->m_nFScore)
				{
					pNeighbour->m_nGScore = pCurrent->m_nGScore + pCurrent->m_anCosts[i];
					pNeighbour->m_nFScore = pNeighbour->m_nGScore + pNeighbour->m_nHScore;
					pNeighbour->m_pPrevious = pCurrent;
				}
			}
		}
	}

	if (bFoundPath)
	{
		Node* pCurrent = pEndNode;
		while (pCurrent)
		{
			path.insert(path.begin(), pCurrent->m_v2Position);
			pCurrent = pCurrent->m_pPrevious;
		}
		return true;
	}
	return false;
}

int Grid::CalculateHeuristic(Node * pNode, Node * pEnd)
{
	int distX = abs(pNode->m_nIndexX - pEnd->m_nIndexX);
	int distY = abs(pNode->m_nIndexY - pEnd->m_nIndexY);

	if (distX > distY)
		return (DIAGONAL_COST * distY) + ADJACENT_COST * (distX - distY);
	else
		return (DIAGONAL_COST * distX) + ADJACENT_COST * (distY - distX);
}


//----------------------------------------------------
//Saves and loads the grid.
//File only stores state of grid at the moment.
//Consider creating a SaveData class in which will
//take all relevant data from 
//----------------------------------------------------
void Grid::Save()
{
	//Get the current grids state.
	//If more than 2 states (eg enums)
	//change 'saved' array type.
	bool saved[GRID_WIDTH * GRID_HEIGHT];
	for (int i = 0; i < GRID_HEIGHT; i++)
	{
		for (int j = 0; j < GRID_WIDTH; j++)
			saved[(i * GRID_WIDTH) + j] = m_apNodeList[i][j]->m_bBlocked;
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
			m_apNodeList[i][j]->m_bBlocked = load[(i * GRID_WIDTH) + j];
	}
}