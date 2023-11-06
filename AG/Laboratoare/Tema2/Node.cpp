#include "Node.h"

Node::Node(QPointF p)
	: coordinate(p)
{

}

Node::Node(const Node& node)
	: coordinate(node.GetCoordinate())
	, value(node.value)
{

}

void Node::SetCoordinate(QPointF p)
{
	coordinate = p;
}

void Node::SetValue(int v)
{
	value = v;
}
QPointF Node::GetCoordinate() const
{
	return coordinate;
}

float Node::GetX() const
{
	return coordinate.x();
}

float Node::GetY() const
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
