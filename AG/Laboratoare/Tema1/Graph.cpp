#include "Graph.h"
#include <fstream>
#include <algorithm>

Graph::Graph()
	: orientated(true)
{

}

Graph::Graph(const Graph& graph)
{
	auto nodes = graph.getNodes();
	auto edges = graph.getEdges();
	for (auto node : nodes)
		this->addNode(node);

	for (auto edge : edges)
		this->addEdge(edge);
}

Graph::~Graph()
{
	reset();
}

void Graph::setOrientation(bool isOrientated)
{
	if (!orientated && isOrientated || orientated == isOrientated)
		return;
	orientated = isOrientated;

	for (auto edge1 : edges)
	{
		for (auto edge2 : edges)
		{
			if (edge1->getFirstNode() == edge2->getSecondNode() && edge1->getSecondNode() == edge1->getFirstNode())
			{
				auto it = std::find(edges.begin(), edges.end(), edge2);
				if (it != edges.end())
					edges.erase(it);
			}
		}
	}
}

void Graph::addNode(QPoint p)
{
	Node* newNode = new Node(p);
	newNode->setValue(nodes.size() + 1);
	nodes.push_back(newNode);
}


void Graph::addNode(Node* n1)
{
	Node* newNode = new Node(*n1);
	nodes.push_back(newNode);
}

void Graph::addEdge(Node* n1, Node* n2)
{
	Edge* newEdge = new Edge(n1, n2);
	edges.push_back(newEdge);
}

void Graph::reset()
{
	for (auto edge : edges)
		delete edge;
	edges.clear();

	for (auto node : nodes)
		delete node;
	nodes.clear();
	orientated = true;
}

std::vector<Node*> Graph::getNodes() const
{
	return nodes;
}

std::vector<Edge*> Graph::getEdges() const
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
