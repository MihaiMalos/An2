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
	~Graph();

	void setOrientation(bool isOrientated);
	void addNode(QPoint p);
	void addEdge(Node* n1, Node* n2);
	
	void reset();

	std::vector<Node*> getNodes();
	std::vector<Edge*> getEdges();
	bool isOrientated();

	std::vector<std::vector<bool>> getAdjacencyMatrix();
	
	void save(std::string fileName);

};

