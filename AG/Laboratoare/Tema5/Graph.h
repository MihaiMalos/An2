#pragma once

#include <vector>
#include "Edge.h"

class Graph
{
	std::vector<Node*> m_nodes;
	std::vector<Edge*> m_edges;

public:
	Graph() = default;
	~Graph();

	void AddNode(QPoint p);
	void AddNode(Node* n1);
	void AddEdge(Node* n1, Node* n2, int weight);
	
	void Reset();

	std::vector<Node*> GetNodes() const;
	std::vector<Edge*> GetEdges() const;

};

