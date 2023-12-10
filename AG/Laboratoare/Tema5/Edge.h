#pragma once
#include "Node.h"
class Edge
{
	Node* m_firstNode, * m_secondNode;
	int m_weight;

public:
	Edge(Node* n1, Node* n2, int weight);

	Node* GetFirstNode() const;
	Node* GetSecondNode() const;
	int GetWeight() const;

};

