#pragma once

#include <vector>
#include "Edge.h"

class Graph
{
	std::vector<Node*> nodes;
	std::vector<Edge*> edges;
	std::vector<std::vector<int>> adjacencyList;

public:
	Graph() = default;
	Graph(const Graph& graph);
	~Graph();

	void addNode(QPoint p);
	void addNode(Node* n1);
	void addEdge(Node* n1, Node* n2);
	
	void reset();

	std::vector<Node*> getNodes() const;
	std::vector<Edge*> getEdges() const;

	std::vector<int> TopologicSort(int source, std::string fileName);
	bool DepthFirstSearch(int source, std::vector<bool>& unvisited);
	void FindRoot();

};

