#pragma once

#include "edge.h"
#include <vector>
#include <fstream>

class Graph
{
    std::vector<NodePtr> m_nodes;
    std::vector<std::vector<int>> m_adjacencyMatrix;

public:
    Graph();

    void AddNode(NodePtr newNode);
    void AddEdge(Edge e);

    std::vector<NodePtr> GetNodes() const;
    std::vector<Edge> GetEdges() const;
    int GetNumberOfNodes() const;

    static std::vector<std::vector<int>> GetAdjacencyLists(std::vector<std::vector<int>> am);
    std::vector<std::pair<int, int>> FindMinimumCut(const std::vector<int>& predecessors) const;

    std::pair<int, std::vector<std::pair<int, int>>> MaximumFlow(int start, int end);
    void PartialDfs(std::vector<int>& predecessors, int positionOfStartNode, int positionOfEndNode, const std::vector<std::vector<int>>& adjList) const;
};

