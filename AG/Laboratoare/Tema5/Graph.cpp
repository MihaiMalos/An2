#include "Graph.h"
#include <fstream>
#include <algorithm>
#include <ranges>
#include <QDebug>
#include <unordered_set>

Graph::~Graph()
{
	Reset();
}

void Graph::AddNode(QPoint p)
{
	Node* newNode = new Node(p);
	newNode->SetValue(m_nodes.size() + 1);
	m_nodes.push_back(newNode);
}


void Graph::AddNode(Node* n1)
{
	Node* newNode = new Node(*n1);
	m_nodes.push_back(newNode);
}

void Graph::AddEdge(Node* n1, Node* n2, int weight)
{
	Edge* newEdge = new Edge(n1, n2, weight);
	m_edges.push_back(newEdge);
}

void Graph::Reset()
{
	for (auto edge : m_edges)
		delete edge;
	m_edges.clear();

	for (auto node : m_nodes)
		delete node;
	m_nodes.clear();
}

std::vector<Node*> Graph::GetNodes() const
{
	return m_nodes;
}

std::vector<Edge*> Graph::GetEdges() const
{
	return m_edges;
}
