#pragma once

#include <vector>
#include "Edge.h"

class Graph
{
	std::vector<Node*> nodes;
	std::vector<Edge*> edges;
	bool orientated;

public:
	Graph();
	Graph(const Graph& graph);
	~Graph();

	void setOrientation(bool isOrientated);
	void addNode(QPoint p);
	void addNode(Node* n1);
	void addEdge(Node* n1, Node* n2);
	
	void reset();

	std::vector<Node*> getNodes() const;
	std::vector<Edge*> getEdges() const;
	bool isOrientated();

	std::vector<std::vector<bool>> getAdjacencyMatrix();
	
	void save(std::string fileName);

};

