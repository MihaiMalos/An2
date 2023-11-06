#include "Node.h"

Node::Node(QPointF p)
	: coordinate(p)
{

}

Node::Node(const Node& node)
	: coordinate(node.getCoordinate())
	, value(node.value)
{

}

void Node::setCoordinate(QPointF p)
{
	coordinate = p;
}

void Node::setValue(int v)
{
	value = v;
}
QPointF Node::getCoordinate() const
{
	return coordinate;
}

float Node::getX() const
{
	return coordinate.x();
}

float Node::getY() const
{
	return coordinate.y();
}

int Node::getValue() const
{
	return value;
}

bool Node::operator==(Node node) const
{
	return this->coordinate == node.coordinate;
}
