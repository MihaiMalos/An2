#pragma once

#include <memory>
#include "node.h"

class Edge
{
private:
    NodePtr m_firstNode, m_secondNode;
    int m_fsCapacity, m_sfCapacity;

public:
    Edge();
    Edge(std::shared_ptr<Node> firstNode, std::shared_ptr<Node> secondNode, int fsCapacity, int sfCapacity);

    std::shared_ptr<Node> getFirstNodePtr() const;
    std::shared_ptr<Node> getSecondNodePtr() const;
    std::pair<int, int> getCapacity() const;
};

