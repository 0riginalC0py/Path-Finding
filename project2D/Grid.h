#pragma once
//#include <vector>
#include "Renderer2D.h"
#include "Vector2.h"
#include "PathHeap.h"
#include "DebugList.h"

#define GRID_WIDTH 38
#define GRID_HEIGHT 38
#define SQUARE_SIZE 50.0f
#define GRID_POS_X 32
#define GRID_POS_Y 32
#define ADJACENT_COST 10
#define DIAGONAL_COST 14


struct Node;

class Grid
{
public:
	Grid(int nWidth, int nHeight, DebugList* pDebugList);
	~Grid();

	void Draw(aie::Renderer2D* pRenderer);

	Node* GetNodeByPosition(Vector2 v2Pos);
	bool FindPath(Vector2 v2Start, Vector2 v2End, std::vector<Vector2>& path);

	aie::Font* m_font;
	
	int CalculateHeuristic(Node* pNode, Node* pEnd);


	void Save();
	void Load();
private:
	Node*** m_apNodeList;

	/*std::vector<Node*>*/PathHeap m_OpenList;
	bool* m_bClosedList;

	DebugList* m_pDebug;

	int m_nWidth;
	int m_nHeight;

};