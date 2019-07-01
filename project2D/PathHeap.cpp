#include "PathHeap.h"
#include "Node.h"

PathHeap::PathHeap()
{

}

PathHeap::~PathHeap()
{

}

int PathHeap::GetCount()
{
	return (int)m_Heap.size();
}



void PathHeap::Push(Node* pNode)
{
	m_Heap.push_back(pNode);
	int Current = (int)m_Heap.size() - 1;
	int Parent = GetParent(Current);
	while (m_Heap[Current]->m_fScore < m_Heap[Parent]->m_fScore)
	{
		Node* swap = m_Heap[Current];
		m_Heap[Current] = m_Heap[Parent];
		m_Heap[Parent] = swap;

		Current = Parent;
		Parent = GetParent(Current);
	}
}


Node* PathHeap::Pop()
{
	Node* pNode = m_Heap[0];

	int Last = (int)m_Heap.size() - 1;

	int current = 0;
	
	m_Heap[current] = m_Heap[Last];
	m_Heap.pop_back();
	int child1Index = GetChild(current, 1);
	int child2Index = GetChild(current, 2);

	int cheapestChild = child1Index;
	
	if (cheapestChild >= m_Heap.size())
		return pNode;

	if (child2Index < m_Heap.size() && m_Heap[child2Index]->m_fScore < m_Heap[cheapestChild]->m_fScore)
		cheapestChild = child2Index;

	while (m_Heap[cheapestChild]->m_fScore < m_Heap[current]->m_fScore)
	{
		Node* swap = m_Heap[cheapestChild];
		m_Heap[cheapestChild] = m_Heap[current];
		m_Heap[current] = swap;

		current = cheapestChild;
		child1Index = GetChild(current, 1);
		child2Index = GetChild(current, 2);

		cheapestChild = child1Index;
		
		if (cheapestChild >= m_Heap.size())
			return pNode;

		if (child2Index < m_Heap.size() && m_Heap[child2Index]->m_fScore < m_Heap[cheapestChild]->m_fScore)
			cheapestChild = child2Index;
	}
		return pNode;
}

void PathHeap::Clear()
{
	m_Heap.clear();
}

bool PathHeap::FindNode(Node* pNode)
{
	return std::find(m_Heap.begin(), m_Heap.end(), pNode) != m_Heap.end();
}


int PathHeap::GetParent(int index)
{
	return (index - 1) / 2;
}


int PathHeap::GetChild(int index, int child)
{
	return (index * 2) + child;
}