#pragma once

#include <QPainter>

class Node
{
	int value;
	QPointF coordinate;

public:
	Node(QPointF p);
	Node(const Node& node);

	void setCoordinate(QPointF p);
	void setValue(int v);

	QPointF getCoordinate() const;
	float getX() const;
	float getY() const;
	int getValue() const;

	bool operator==(Node node) const;
};

