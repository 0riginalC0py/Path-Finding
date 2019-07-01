#pragma once
#include "Renderer2D.h"
#include "Vector2.h"
#include <vector>
#include "PathHeap.h"


class BB;


struct Node;

class Grid
{
public:
	Grid(int sizeWidth, int sizeHeight);
	~Grid();
	
	float FindEnd(Node* current, Node* end);

	bool FindPath(Vector2 start, Vector2 end, std::vector<Vector2>& path);
	void Draw(aie::Renderer2D* renderer, BB levelManager);
	Node* GetNodeByPos(Vector2 pos);

	

	void Save();
	void Load();
private:
	int m_Height;
	int m_Width;


	//void SortOpenList();
	
	//Used for saving.
	//I think this is dumb and can
	//be done better.
	

	Node*** m_NodeList;
	bool* m_ClosedList;

	//std::vector<Node*> m_OpenList;
	PathHeap m_OpenList;
};

