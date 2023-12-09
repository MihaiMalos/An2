#include "Graph.h"
#include <fstream>
#include <algorithm>
#include <ranges>
#include "DisjointSet.h"
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

std::vector<Edge*> Graph::KruskalTree()
{
	std::vector<Edge*> treeEdges;

	std::ranges::sort(m_edges, [](Edge* firstEdge, Edge* secondEdge) {
	return firstEdge->GetWeight() < secondEdge->GetWeight();
	});
	DisjointSet set(m_nodes.size());

	for (auto edge : m_edges)
	{
		int rootFirstNode = set.Find(edge->GetFirstNode()->GetValue()-1);
		int rootSecondNode = set.Find(edge->GetSecondNode()->GetValue()-1);

		if (rootFirstNode != rootSecondNode)
		{
			treeEdges.push_back(edge);
			set.Merge(rootFirstNode, rootSecondNode);
		}
	}

	return treeEdges;
	
}

std::vector<Edge*> Graph::BoruvkaTree()
{
	std::vector<Edge*> treeEdges;
	DisjointSet set(m_nodes.size());

	while (treeEdges.size() != m_nodes.size() - 1)
	{
		std::vector<int> cheapest(m_nodes.size(), -1);
		for (int index = 0; index < m_edges.size(); index++)
		{
			auto edge = m_edges[index];
			int rootFirstNode = set.Find(edge->GetFirstNode()->GetValue() - 1);
			int rootSecondNode = set.Find(edge->GetSecondNode()->GetValue() - 1);

			if (rootFirstNode == rootSecondNode) continue;
			if (cheapest[rootFirstNode] == -1 || edge->GetWeight() < m_edges[cheapest[rootFirstNode]]->GetWeight())
			{
				cheapest[rootFirstNode] = index;
			}
			if (cheapest[rootSecondNode] == -1 || edge->GetWeight() < m_edges[cheapest[rootSecondNode]]->GetWeight())
			{
				cheapest[rootSecondNode] = index;
			}
		}

		for (int index = 0; index < m_nodes.size(); index++)
		{
			if (cheapest[index] != -1)
			{
				auto edge = m_edges[cheapest[index]];
				int rootFirstNode = set.Find(edge->GetFirstNode()->GetValue() - 1);
				int rootSecondNode = set.Find(edge->GetSecondNode()->GetValue() - 1);

				if (rootFirstNode != rootSecondNode)
				{
					treeEdges.push_back(edge);
					set.Merge(rootFirstNode, rootSecondNode);
				}
			}
		}
	}



	return treeEdges;
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
