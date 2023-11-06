#pragma once
#include "Node.h"
class Edge
{
	Node* firstNode, * secondNode;

public:
	Edge(Node* n1, Node* n2);

	Node* getFirstNode();
	Node* getSecondNode();
};

