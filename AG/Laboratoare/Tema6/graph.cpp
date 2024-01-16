#include "graph.h"
#include <stack>
#include <unordered_map>

Graph::Graph()
{
}

void Graph::AddNode(NodePtr newNode)
{
	m_nodes.push_back(newNode);

	for (auto& column : m_adjacencyMatrix)
		column.push_back(0.f);

	m_adjacencyMatrix.emplace_back(std::vector<int>(GetNumberOfNodes(), 0.0f));
}

void Graph::AddEdge(Edge e)
{
	m_adjacencyMatrix[e.getFirstNodePtr()->GetInfo()][e.getSecondNodePtr()->GetInfo()] = e.getCapacity().first;
	m_adjacencyMatrix[e.getSecondNodePtr()->GetInfo()][e.getFirstNodePtr()->GetInfo()] = e.getCapacity().second;
}

std::vector<NodePtr> Graph::GetNodes() const
{
	return m_nodes;
}

std::vector<Edge> Graph::GetEdges() const
{
	std::vector<Edge> edges;

	for (int i = 0; i < GetNumberOfNodes(); i++)
	{
		for (int j = i + 1; j < GetNumberOfNodes(); j++)
			if (m_adjacencyMatrix[i][j] || m_adjacencyMatrix[j][i])
				edges.emplace_back(m_nodes[i], m_nodes[j], m_adjacencyMatrix[i][j], m_adjacencyMatrix[j][i]);
	}

	return edges;
}

void Graph::PartialDfs(std::vector<int>& predecessors, int positionOfStartNode, int positionOfEndNode, const std::vector<std::vector<int>>& adjList) const
{
	std::stack<int> unprocessed;

	std::vector<bool> unvisited;
	unvisited.resize(GetNumberOfNodes(), true);

	unprocessed.push(positionOfStartNode);
	unvisited[positionOfStartNode] = false;


	while (!unprocessed.empty()) {
		int current = unprocessed.top();

		bool existsNotVisited = 0;
		for (auto& node : adjList[current]) {
			if (unvisited[node]) {
				existsNotVisited = true;
				unvisited[node] = false;
				unprocessed.push(node);
				predecessors[node] = current;
				break;
			}
		}

		if (!existsNotVisited) {
			unprocessed.pop();
		}
	}
}


std::vector<std::vector<int>> Graph::GetAdjacencyLists(std::vector<std::vector<int>> am)
{
	std::vector<std::vector<int>> lst;
	lst.resize(am.size());

	for(int i=0; i<am.size(); i++)
	{
		for(int j=0; j<am.size(); j++)
		{
			if (am[i][j] > 0)
				lst[i].push_back(j);
		}
	}

	return lst;
}

std::vector<std::pair<int, int>> Graph::FindMinimumCut(const std::vector<int>& predecessors) const
{
	std::vector<int> accesible(predecessors.size(), false);
	for(int i=0; i<predecessors.size(); i++)
		if (predecessors[i] != -1)
			accesible[i] = true;
	accesible[0] = true;
		
	std::vector<std::pair<int, int>> result;
	auto edges = GetEdges();
	for(const Edge& edge : edges)
	{
		if (accesible[edge.getFirstNodePtr()->GetInfo()] != accesible[edge.getSecondNodePtr()->GetInfo()])
			result.emplace_back(edge.getFirstNodePtr()->GetInfo(), edge.getSecondNodePtr()->GetInfo());
	}

	return result;
}

std::pair<int, std::vector<std::pair<int, int>>> Graph::MaximumFlow(int start, int end)
{
	int currentFlow = 0;

	while(true)
	{
		auto adjList = GetAdjacencyLists(m_adjacencyMatrix);
		std::vector<int> predecessors(m_adjacencyMatrix.size(), -1);

		PartialDfs(predecessors, start, end, adjList);
		if (predecessors[end] == -1) return { currentFlow, FindMinimumCut(predecessors) };


		int minCurrentFlow = INT32_MAX;
		int curentNode = end;
		while(predecessors[curentNode] != -1)
		{
			minCurrentFlow = std::min(minCurrentFlow, m_adjacencyMatrix[predecessors[curentNode]][curentNode]);
			curentNode = predecessors[curentNode];
		}

		curentNode = end;
		while (predecessors[curentNode] != -1)
		{
			m_adjacencyMatrix[predecessors[curentNode]][curentNode] -= minCurrentFlow;
			m_adjacencyMatrix[curentNode][predecessors[curentNode]] += minCurrentFlow;
			curentNode = predecessors[curentNode];
		}

		currentFlow += minCurrentFlow;
	}
}

int Graph::GetNumberOfNodes() const
{
	return m_nodes.size();
}