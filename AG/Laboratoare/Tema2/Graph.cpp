#include "Graph.h"
#include <fstream>
#include <algorithm>
#include <QDebug>

Graph::Graph(std::vector<std::vector<int>> new_matrix, EDirection position)
	: node_radius(20.0f)
	, matrix(new_matrix)
	, position(position)
{

}

Graph::Graph(const Graph& graph)
{
	//auto nodes = graph.getNodes();
	///*auto edges = graph.getEdges();*/
	//for (auto node : nodes)
	//	addNode(*node);

}

Graph::~Graph()
{
	reset();
}

void Graph::initGraph(QSize screenSize)
{
	QSizeF offset = directionToOffset(screenSize);
	int rows = matrix.size();
	int columns = matrix[0].size();

	for (int rowIndex = 0; rowIndex < rows; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < columns; columnIndex++)
		{
			if (matrix[rowIndex][columnIndex] != 0)
			{
				int value = rowIndex * columns + columnIndex;
				addNode(QPointF(0, 0), value);			
			}
		}
	}
	for (int rowIndex = 0; rowIndex < rows; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < columns; columnIndex++)
		{
			if (matrix[rowIndex][columnIndex] != 0)
			{
				int value = rowIndex * columns + columnIndex;
				if (rowIndex + 1 < rows && matrix[rowIndex + 1][columnIndex] != 0)
					addEdge(nodes.at(value), nodes.at(value + columns));
				if (columnIndex + 1 < columns && matrix[rowIndex][columnIndex + 1] != 0)
					addEdge(nodes.at(value), nodes.at(value + 1));
			}
		}
	}

}

QSizeF Graph::directionToOffset(QSize screenSize)
{
	switch (position)
	{
	case EDirection::leftTop:
		return QSizeF(0, 0);
	case EDirection::rightTop:
		return QSizeF(screenSize.width() / 2.0f, 0);
	case EDirection::leftBottom:
		return QSizeF(0, screenSize.height() / 2.0f);
	case EDirection::rightBottom:
		return QSizeF(screenSize.width() / 2.0f, screenSize.height() / 2.0f);
	}
}

void Graph::addNode(QPointF p, int value)
{
	Node* newNode = new Node(p);
	newNode->setValue(nodes.size() + 1);
	nodes.emplace(value, newNode);
}


void Graph::addNode(Node n1)
{
	//Node* newNode = new Node(n1);
	//nodes.push_back(newNode);
}

void Graph::addEdge(Node* n1, Node* n2)
{
	auto it = std::find_if(edges.begin(), edges.end(), [&](Edge* edge) {
		return edge->getFirstNode() == n2 && edge->getSecondNode() == n1;
		});

	if (it != edges.end()) return;
	Edge* newEdge = new Edge(n1, n2);
	edges.push_back(newEdge);
}

void Graph::updateSize(QSize screenSize)
{
	QSizeF offset = directionToOffset(screenSize);
	int rows = matrix.size();
	int columns = matrix[0].size();
	for (int rowIndex = 0; rowIndex < rows; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < columns; columnIndex++)
		{
			if (matrix[rowIndex][columnIndex] != 0)
			{
				int value = rowIndex * columns + columnIndex;
				float x = (screenSize.width() / (2.0f * columns)) * columnIndex;
				float y = (screenSize.height() / (2.0f * rows)) * rowIndex;
				QPointF offsetToCenter = QPointF((screenSize.width() / (2.0f * columns)), (screenSize.height() / (2.0f * rows)));
				float newX = x + offset.width() - 0.05 * screenSize.width();
				float newY = y + offset.height() - 0.05 * screenSize.height();
				nodes.at(value)->setCoordinate(QPointF(newX, newY) + offsetToCenter);
				
			}
		}
	}
	node_radius = fmin(screenSize.width(), screenSize.height()) / 45.0f;
}

void Graph::reset()
{
	for (auto edge : edges)
		delete edge;
	edges.clear();

	for (auto node = nodes.begin(); node != nodes.end(); node++)
		delete node->second;
	nodes.clear();
}

std::unordered_map<int, Node*> Graph::getNodes() const
{
	return nodes;
}

std::vector<Edge*> Graph::getEdges() const
{
	return edges;
}

std::vector<std::vector<int>> Graph::getMatrix() const
{
	return matrix;
}

float Graph::getRadius() const
{
	return node_radius;
}
