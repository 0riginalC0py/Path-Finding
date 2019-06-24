#pragma once
#include <vector>
struct Node;

class PathHeap
{
public:
	PathHeap();
	~PathHeap();

	void Push(Node* pNode);
	Node* Pop();
	int GetCount();
	void Clear();

	bool Find(Node* pNode);
private:
	int GetParent(int index);
	int GetChild(int index, int child);

	std::vector<Node*> m_NodeHeap;
};