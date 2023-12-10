#include "Edge.h"

Edge::Edge(Node* n1, Node* n2, int weight)
	: m_firstNode(n1)
	, m_secondNode(n2)
	, m_weight(weight)
{
	// Empty
}

Node* Edge::GetFirstNode() const
{
	return m_firstNode;
}

Node* Edge::GetSecondNode() const
{
	return m_secondNode;
}

int Edge::GetWeight() const
{
	return m_weight;
}


