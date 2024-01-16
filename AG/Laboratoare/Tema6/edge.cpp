#include "edge.h"

Edge::Edge()
    : m_fsCapacity(0)
    , m_sfCapacity(0)
{
    // Empty
}

Edge::Edge(std::shared_ptr<Node> firstNode, std::shared_ptr<Node> secondNode, int fsCapacity, int sfCapacity)
    : Edge()

{
    m_firstNode = firstNode;
    m_secondNode = secondNode;

    m_fsCapacity = fsCapacity;
    m_sfCapacity = sfCapacity;
}

std::shared_ptr<Node> Edge::getFirstNodePtr() const
{
    return m_firstNode;
}

std::shared_ptr<Node> Edge::getSecondNodePtr() const
{
    return m_secondNode;
}

std::pair<int, int> Edge::getCapacity() const
{
    return {m_fsCapacity, m_sfCapacity};
}
