#include "Graph.h"
#include <fstream>

void Graph::setOrientation(bool isOrientated)
{
	orientated = isOrientated;
}

void Graph::addNode(QPoint p)
{
	Node* newNode = new Node(p);
	newNode->setValue(nodes.size() + 1);
	nodes.push_back(newNode);
}

void Graph::addEdge(Node* n1, Node* n2)
{
	Edge* newEdge = new Edge(n1, n2);
	edges.push_back(newEdge);
}

std::vector<Node*> Graph::getNodes()
{
	return nodes;
}

std::vector<Edge*> Graph::getEdges()
{
	return edges;
}

bool Graph::isOrientated()
{
	return orientated;
}

std::vector<std::vector<bool>> Graph::getAdjacencyMatrix()
{
	std::vector<std::vector<bool>> matrix(nodes.size(), std::vector<bool>(nodes.size(), false));
	for (auto edge : edges)
	{
		int firstNodeValue = edge->getFirstNode()->getValue();
		int secondNodeValue = edge->getSecondNode()->getValue();

		matrix[firstNodeValue-1][secondNodeValue-1] = true;

		if (!orientated) matrix[secondNodeValue-1][firstNodeValue-1] = true;
	}
	return matrix;
}

void Graph::save(std::string fileName)
{
	std::ofstream file(fileName);
	auto matrix = getAdjacencyMatrix();
	file << nodes.size() << std::endl;
	for (auto row : matrix)
	{
		for (auto element : row)
		{
			file << element << " ";
		}
		file << std::endl;
	}
}
