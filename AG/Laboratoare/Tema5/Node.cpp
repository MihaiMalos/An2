#include "Node.h"

Node::Node(QPoint p)
	: coordinate(p)
{

}

Node::Node(const Node& node)
	: coordinate(node.GetCoordinate())
	, value(node.value)
{

}

void Node::SetCoordinate(QPoint p)
{
	coordinate = p;
}

void Node::SetValue(int v)
{
	value = v;
}
QPoint Node::GetCoordinate() const
{
	return coordinate;
}

int Node::GetX() const
{
	return coordinate.x();
}

int Node::GetY() const
{
	return coordinate.y();
}

int Node::GetValue() const
{
	return value;
}

bool Node::operator==(Node node) const
{
	return this->coordinate == node.coordinate;
}
