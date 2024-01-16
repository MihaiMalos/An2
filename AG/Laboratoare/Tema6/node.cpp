#include "node.h"

Node::Node(int inf)
{
	info = inf;
}

Node::Node(QPointF cood, int inf)
{
	coord = cood;
	info = inf;
}

QPointF Node::GetCoord() const
{
	return coord;
}

int Node::GetInfo() const
{
	return info;
}

void Node::SetInfo(int inf)
{
	info = inf;
}

bool Node::operator==(const Node& other) const
{
	return coord == other.coord;
}

float Node::GetDistance(const QPointF& a, const QPointF& b)
{
	return sqrt(std::pow((a.x() - b.x()),2) + std::pow((a.y() - b.y()),2));
}
