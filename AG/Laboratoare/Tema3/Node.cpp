#include "Node.h"

Node::Node(QPoint p)
	: coordinate(p)
{

}

Node::Node(const Node& node)
	: coordinate(node.getCoordinate())
	, value(node.value)
{

}

void Node::setCoordinate(QPoint p)
{
	coordinate = p;
}

void Node::setValue(int v)
{
	value = v;
}
QPoint Node::getCoordinate() const
{
	return coordinate;
}

int Node::getX() const
{
	return coordinate.x();
}

int Node::getY() const
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
