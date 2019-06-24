#pragma once
//#include <vector>
#include "Renderer2D.h"
#include "Vector2.h"
#include "PathHeap.h"

struct Node;

class Grid
{
public:
	Grid(int nWidth, int nHeight);
	~Grid();

	void Draw(aie::Renderer2D* pRenderer);

	Node* GetNodeByPosition(Vector2 v2Pos);
	bool FindPath(Vector2 v2Start, Vector2 v2End, std::vector<Vector2>& path);

	aie::Font* m_font;
	
	int CalculateHeuristic(Node* pNode, Node* pEnd);

private:
	Node*** m_apNodeList;

	/*std::vector<Node*>*/PathHeap m_OpenList;
	bool* m_bClosedList;

	int m_nWidth;
	int m_nHeight;
};