#include "PathHeap.h"
#include "Node.h"
#include <algorithm>

PathHeap::PathHeap()
{

}

PathHeap::~PathHeap()
{

}

void PathHeap::Push(Node* pNode)
{
	m_NodeHeap.push_back(pNode);

	int nCurrent = m_NodeHeap.size() - 1;
	int nParent = GetParent(nCurrent);

	while (m_NodeHeap[nCurrent]->m_nFScore < m_NodeHeap[nParent]->m_nFScore)
	{
		Node* pSwap = m_NodeHeap[nCurrent];
		m_NodeHeap[nCurrent] = m_NodeHeap[nParent];
		m_NodeHeap[nParent] = pSwap;

		nCurrent = nParent;
		nParent = GetParent(nCurrent);
	}
}

Node* PathHeap::Pop()
{
	Node* pNode = m_NodeHeap[0];

	int nLast = m_NodeHeap.size() - 1;

	int nCurrent = 0;
	m_NodeHeap[nCurrent] = m_NodeHeap[nLast];
	m_NodeHeap.pop_back();

	int nChild1Index = GetChild(nCurrent, 1);
	int nChild2Index = GetChild(nCurrent, 2);

	int nCheapestChildIndex = nChild1Index;
	if (nCheapestChildIndex >= m_NodeHeap.size())
		return pNode;

	if (nChild2Index < m_NodeHeap.size() && m_NodeHeap[nChild2Index]->m_nFScore < m_NodeHeap[nCheapestChildIndex]->m_nFScore)
		nCheapestChildIndex = nChild2Index;

	while (m_NodeHeap[nCheapestChildIndex]->m_nFScore < m_NodeHeap[nCurrent]->m_nFScore)
	{
		Node* pSwap = m_NodeHeap[nCheapestChildIndex];
		m_NodeHeap[nCheapestChildIndex] = m_NodeHeap[nCurrent];
		m_NodeHeap[nCurrent] = pSwap;

		nCurrent = nCheapestChildIndex;
		nChild1Index = GetChild(nCurrent, 1);
		nChild2Index = GetChild(nCurrent, 2);

		nCheapestChildIndex = nChild1Index;
		if (nCheapestChildIndex >= m_NodeHeap.size())
			return pNode;

		if (nChild2Index < m_NodeHeap.size() && m_NodeHeap[nChild2Index]->m_nFScore < m_NodeHeap[nCheapestChildIndex]->m_nFScore)
			nCheapestChildIndex = nChild2Index;
	}

	return pNode;
}

int PathHeap::GetCount()
{
	return m_NodeHeap.size();
}

void PathHeap::Clear()
{
	m_NodeHeap.clear();
}

bool PathHeap::Find(Node * pNode)
{
	return std::find(m_NodeHeap.begin(), m_NodeHeap.end(), pNode) != m_NodeHeap.end();
}

int PathHeap::GetParent(int index)
{
	return (index - 1) / 2;
}

int PathHeap::GetChild(int index, int child)
{
	return (2 * index) + child;
}
