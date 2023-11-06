#include "Edge.h"

Edge::Edge(Node* n1, Node* n2)
	: firstNode(n1)
	, secondNode(n2)
{

}

Node* Edge::GetFirstNode()
{
	return firstNode;
}

Node* Edge::GetSecondNode()
{
	return secondNode;
}

