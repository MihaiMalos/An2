#include "Graph.h"
#include <fstream>
#include <algorithm>
#include <QDebug>
#include <queue>

Graph::Graph(std::vector<std::vector<int>> new_matrix)
	: nodeRadius(20.0f)
	, matrix(new_matrix)
{

}

Graph::~Graph()
{
	Reset();
}

void Graph::InitGraph(QSize screenSize)
{
	int rows = matrix.size();
	int columns = matrix[0].size();

	for (int rowIndex = 0; rowIndex < rows; rowIndex++)
	{
		for (int columnIndex = 0; columnIndex < columns; columnIndex++)
		{
			int elementType = matrix[rowIndex][columnIndex];
			if (elementType != 0)
			{
				int value = rowIndex * columns + columnIndex;
				AddNode(QPointF(0, 0), value);	
				if (elementType == 2)
					exitNodes.push_back(nodes.at(value));
				else if (elementType == 3)
					entryNode = nodes.at(value);
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
					AddEdge(nodes.at(value), nodes.at(value + columns));
				if (columnIndex + 1 < columns && matrix[rowIndex][columnIndex + 1] != 0)
					AddEdge(nodes.at(value), nodes.at(value + 1));
			}
		}
	}
	InitAdjacencyList();
}

void Graph::AddNode(QPointF p, int value)
{
	Node* newNode = new Node(p);
	newNode->SetValue(nodes.size());
	allNodes.push_back(newNode);
	nodes.emplace(value, newNode);
}


void Graph::AddEdge(Node* n1, Node* n2)
{
	auto it = std::find_if(edges.begin(), edges.end(), [&](Edge* edge) {
		return edge->GetFirstNode() == n2 && edge->GetSecondNode() == n1;
		});

	if (it != edges.end()) return;
	Edge* newEdge = new Edge(n1, n2);
	edges.push_back(newEdge);
}

void Graph::UpdateSize(QSize screenSize)
{
	QSizeF offset = QSizeF(screenSize.width() / 2.0f, 0);
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
				nodes.at(value)->SetCoordinate(QPointF(newX, newY) + offsetToCenter);
				
			}
		}
	}
	nodeRadius = fmin(screenSize.width(), screenSize.height()) / 45.0f;
}

std::vector<Node*> Graph::ComputeMazePaths()
{
	std::vector<Node*> exitPaths;
	for (auto node : exitNodes)
	{
		auto path = BreadthFirstSearch(node);
		exitPaths.insert(exitPaths.end(), path.begin(), path.end());
	}
	return exitPaths;
}

void Graph::Reset()
{
	for (auto edge : edges)
		delete edge;
	edges.clear();

	for (auto node = nodes.begin(); node != nodes.end(); node++)
		delete node->second;
	nodes.clear();
}

std::vector<Node*> Graph::BreadthFirstSearch(Node* exitNode)
{
	std::queue<Node*> visited;
	std::vector<int> predecessors(nodes.size(), 0), length(nodes.size(), 0);
	std::vector<bool> unvisited(nodes.size(), true);
	std::vector<Node*> path;


	unvisited[entryNode->GetValue()] = false;
	visited.push(entryNode);

	while (!visited.empty())
	{
		auto currentNode = visited.front();
		auto currentNodeValue = visited.front()->GetValue();

		if (currentNode == exitNode)
		{
			while (currentNode != entryNode)
			{
				path.push_back(currentNode);
				currentNode = allNodes[predecessors[currentNodeValue]];
				currentNodeValue = currentNode->GetValue();
			}
			return path;
		}

		for (auto neighbor : adjancencyList[currentNodeValue])
		{
			if (unvisited[neighbor])
			{
				unvisited[neighbor] = false;
				visited.push(allNodes[neighbor]);
				predecessors[neighbor] = currentNodeValue;
				length[neighbor] = length[currentNodeValue] + 1;
			}
		}
		visited.pop();
	}
}

void Graph::InitAdjacencyList()
{
	adjancencyList.resize(nodes.size());
	for (auto edge : edges)
	{
		auto firstNode = edge->GetFirstNode()->GetValue();
		auto secondNode = edge->GetSecondNode()->GetValue();

		adjancencyList[firstNode].push_back(secondNode);
		adjancencyList[secondNode].push_back(firstNode);
		
	}
}

std::unordered_map<int, Node*> Graph::GetNodes() const
{
	return nodes;
}

std::vector<Edge*> Graph::GetEdges() const
{
	return edges;
}

std::vector<Node*> Graph::GetExitNodes() const
{
	return exitNodes;
}

Node* Graph::GetEntryNode() const
{
	return entryNode;
}

std::vector<std::vector<int>> Graph::GetMatrix() const
{
	return matrix;
}

float Graph::GetRadius() const
{
	return nodeRadius;
}
