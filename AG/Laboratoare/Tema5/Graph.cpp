#include "Graph.h"
#include <fstream>
#include <algorithm>
#include <ranges>
#include <QDebug>
#include <queue>

Graph::~Graph()
{
	Reset();
}

void Graph::AddNode(QPoint p)
{
	Node* newNode = new Node(p);
	newNode->SetValue(m_nodes.size() + 1);
	m_nodes.push_back(newNode);
	adjacencyList.push_back(std::vector<Edge*>());
}


void Graph::AddNode(Node* n1)
{
	Node* newNode = new Node(*n1);
	m_nodes.push_back(newNode);
	adjacencyList.push_back(std::vector<Edge*>());
}

void Graph::AddEdge(Node* n1, Node* n2, int weight)
{
	Edge* newEdge = new Edge(n1, n2, weight);
	m_edges.push_back(newEdge);
	adjacencyList[n1->GetValue()-1].push_back(newEdge);
}

std::vector<Node*> Graph::DijkstraPath(Node* startNode, Node* endNode)
{
	struct QueueElement
	{
		Node* node;
		float distance;
		QueueElement(Node* node, float distance) : node(node), distance(distance) {}
		bool operator < (const QueueElement& other) const { return distance > other.distance; }
	};

	std::vector<Node*> parent(m_nodes.size());
	std::vector<bool> visited(m_nodes.size(), false);
	std::vector<float> distance(m_nodes.size(), std::numeric_limits<float>::infinity());
	std::priority_queue<QueueElement> queue;

	distance[startNode->GetValue() - 1] = 0;
	queue.emplace( startNode, 0 );

	while (!queue.empty())
	{
		auto currentNode = queue.top().node;
		int currentNodeValue = currentNode->GetValue()-1;

		if (visited[currentNodeValue])
		{
			queue.pop();
			continue;
		}
		visited[currentNodeValue] = true;
		if (currentNode == endNode) break;

		for (auto neighbour : adjacencyList[currentNodeValue])
		{
			auto neighbourValue = neighbour->GetSecondNode()->GetValue()-1;
			auto edgeCost = neighbour->GetWeight();
			if (visited[neighbourValue]) continue;
			if (distance[neighbourValue] > edgeCost + distance[currentNodeValue])
			{
				distance[neighbourValue] = edgeCost + distance[currentNodeValue];
				parent[neighbourValue] = currentNode;

				queue.emplace(neighbour->GetSecondNode(), distance[neighbourValue]);
			}
		}
		queue.pop();
	}

	if (queue.empty()) return std::vector<Node*>();

	std::vector<Node*> path;
	int nodeValue = endNode->GetValue()-1;
	while (parent[nodeValue]) 
	{
		path.emplace_back(m_nodes[nodeValue]);
		nodeValue = parent[nodeValue]->GetValue()-1;
	}

	return path;


}
void Graph::Reset()
{
	for (auto edge : m_edges)
		delete edge;
	m_edges.clear();

	for (auto node : m_nodes)
		delete node;
	m_nodes.clear();
	adjacencyList.clear();
}

std::vector<Node*> Graph::GetNodes() const
{
	return m_nodes;
}

std::vector<Edge*> Graph::GetEdges() const
{
	return m_edges;
}
