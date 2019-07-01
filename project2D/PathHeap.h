#pragma once
#include <vector>

struct Node;

class PathHeap
{
public:

	PathHeap();
	~PathHeap();


	void Push(Node* Node);
	int GetCount();
	Node* Pop();

	void Clear();
	bool FindNode(Node* pm_heapNode);

private:
	int GetParent(int index);
	int GetChild(int index, int child);


	std::vector<Node*> m_Heap;

};