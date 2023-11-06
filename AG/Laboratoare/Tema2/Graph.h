#pragma once

#include "Edge.h"

class Graph
{
public:
	Graph(std::vector<std::vector<int>> new_matrix);
	~Graph();

	void InitGraph(QSize screenSize);
	void AddNode(QPointF p, int value);
	void AddEdge(Node* n1, Node* n2);

	std::unordered_map<int, Node*> GetNodes() const;
	std::vector<Edge*> GetEdges() const;
	std::vector<Node*> GetExitNodes() const;
	Node* GetEntryNode() const;
	std::vector<std::vector<int>> GetMatrix() const;
	float GetRadius() const;

	void UpdateSize(QSize screenSize);
	std::vector<Node*> ComputeMazePaths();
	
private:
	void Reset();
	std::vector<Node*> BreadthFirstSearch(Node* exitNode);
	void InitAdjacencyList();

private:
	std::unordered_map<int, Node*> nodes;
	std::vector<Node*> allNodes;
	std::vector<Edge*> edges;
	std::vector<std::vector<int>> matrix;
	std::vector<std::vector<int>> adjancencyList;

	Node* entryNode;
	std::vector<Node*> exitNodes;

	float nodeRadius;



};

