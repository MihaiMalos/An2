#pragma once

#include "Edge.h"

enum class EDirection {
	leftTop,
	rightTop,
	leftBottom,
	rightBottom,
};

class Graph
{
	std::unordered_map<int, Node*> nodes;
	std::vector<Edge*> edges;
	std::vector<std::vector<int>> matrix;
	float node_radius;
	EDirection position;

public:
	Graph(std::vector<std::vector<int>> new_matrix, EDirection position);
	Graph(const Graph& graph);
	~Graph();

	void initGraph(QSize screenSize);
	QSizeF directionToOffset(QSize screenSize);

	void addNode(QPointF p, int value);
	void addNode(Node n1);
	void addEdge(Node* n1, Node* n2);
	void updateSize(QSize screenSize);
	
	void reset();

	std::unordered_map<int, Node*> getNodes() const;
	std::vector<Edge*> getEdges() const;
	std::vector<std::vector<int>> getMatrix() const;
	float getRadius() const;



};

