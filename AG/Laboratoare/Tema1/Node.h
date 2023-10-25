#pragma once

#include <QPainter>

class Node
{
	int value;
	QPoint coordinate;

public:
	Node(QPoint p);
	Node(const Node& node);

	void setCoordinate(QPoint p);
	void setValue(int v);

	QPoint getCoordinate() const;
	int getX() const;
	int getY() const;
	int getValue() const;

	bool operator==(Node node) const;
};

