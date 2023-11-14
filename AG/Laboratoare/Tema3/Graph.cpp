#include "Graph.h"
#include <fstream>
#include <algorithm>
#include <stack>
#include <limits>
#include <QDebug>

Graph::Graph(const Graph& graph)
{
	auto nodes = graph.getNodes();
	auto edges = graph.getEdges();
	for (auto node : nodes)
		this->addNode(node);

}

Graph::~Graph()
{
	reset();
}

void Graph::addNode(QPoint p)
{
	Node* newNode = new Node(p);
	newNode->setValue(nodes.size());
	nodes.push_back(newNode);
	adjacencyList.push_back(std::vector<int>());
}


void Graph::addNode(Node* n1)
{
	Node* newNode = new Node(*n1);
	nodes.push_back(newNode);
	adjacencyList.push_back(std::vector<int>());
}

void Graph::addEdge(Node* n1, Node* n2)
{
	Edge* newEdge = new Edge(n1, n2);
	edges.push_back(newEdge);
	adjacencyList[n1->getValue()].push_back(n2->getValue());
}

void Graph::reset()
{
	for (auto edge : edges)
		delete edge;
	edges.clear();

	for (auto node : nodes)
		delete node;
	nodes.clear();

	adjacencyList.clear();
}

std::vector<Node*> Graph::getNodes() const
{
	return nodes;
}

std::vector<Edge*> Graph::getEdges() const
{
	return edges;
}

std::vector<int> Graph::TopologicSort(int source, std::string fileName)
{
	if (nodes.empty()) return std::vector<int>();

	int nodesNumber = nodes.size();
	std::stack<int> visited, finished;
	std::vector<bool> unvisited(nodesNumber, true), inStack(nodesNumber, false);
	std::vector<int> predecessorList(nodesNumber), startingTime(nodesNumber), finishingTime(nodesNumber);

	visited.push(source);

	for (int index = 0; index < nodesNumber; index++)
	{
		predecessorList[index] = -1;
		startingTime[index] = std::numeric_limits<int>::infinity();
		finishingTime[index] = std::numeric_limits<int>::infinity();

		if (index == source) unvisited[index] = false;
	}

	startingTime[source] = 1;
	int time = 1;

	while (finished.size() != nodes.size())
	{
		while (!visited.empty())
		{
			int currentNode = visited.top();
			inStack[currentNode] = true;
			
			bool hasNeighbour = false;
			for (auto node : adjacencyList[currentNode])
			{
				if (inStack[node]) {
					std::ofstream fout(fileName);
					fout << "The graph has cycles" << std::endl;
					fout.close();

					return std::vector<int>();
				}
				if (unvisited[node])
				{
					unvisited[node] = false;
					visited.push(node);
					predecessorList[node] = currentNode;
					startingTime[node] = ++time;
					hasNeighbour = true;
					break;
				}
			}
			if (!hasNeighbour)
			{
				inStack[currentNode] = false;
				visited.pop();
				finished.push(currentNode);
				finishingTime[currentNode] = ++time;
			}
		}
		if (visited.empty())
		{
			for (int index = 0; index < unvisited.size(); index++)
			{
				if (unvisited[index])
				{
					unvisited[index] = false;
					visited.push(index);
					startingTime[index] = ++time;
					break;
				}
			}
		}
	}
	
	std::ofstream fout(fileName);
	while (!finished.empty())
	{
		fout << finished.top() << " ";
		finished.pop();
	}

	return predecessorList;



}

bool Graph::DepthFirstSearch(int source, std::vector<bool>& unvisited)
{
	if (edges.size() != nodes.size() - 1) return false;

	std::stack<int> visited, finished;
	std::vector<bool> inStack(nodes.size(), false);

	visited.push(source);
	unvisited[source] = false;

	while (!visited.empty())
	{
		int currentNode = visited.top();
		inStack[currentNode] = true;

		bool hasNeighbour = false;
		for (auto node : adjacencyList[currentNode])
		{
			if (inStack[node]) return false;
			if (unvisited[node])
			{

				unvisited[node] = false;
				visited.push(node);
				hasNeighbour = true;
				break;
			}
		}
		if (!hasNeighbour)
		{
			inStack[currentNode] = false;
			visited.pop();
			finished.push(currentNode);
		}
	}
	if (finished.size() != nodes.size()) return false;
	return true;
}

void Graph::FindRoot()
{
	std::vector<bool> unvisited(nodes.size(), true);
	int root;

	for (auto node : nodes)
	{
		int nodeValue = node->getValue();
		if (unvisited[nodeValue])
		{
			root = nodeValue;
			DepthFirstSearch(nodeValue, unvisited);
		}
	}

	unvisited = std::vector<bool>(nodes.size(), true);

	bool ok = DepthFirstSearch(root, unvisited);


	for (auto node : nodes)
	{
		int nodeValue = node->getValue();
		if (unvisited[nodeValue]) 
		{
			ok = false;
			break;
		}
	}

	if (ok)
	{
		qDebug() << "Root is:" << root;
	}
	else
	{
		qDebug() << "Graph is not a tree";
	}
}
