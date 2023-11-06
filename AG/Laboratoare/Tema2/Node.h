#pragma once

#include <QPainter>

class Node
{
	int value;
	QPointF coordinate;

public:
	Node(QPointF p);
	Node(const Node& node);

	void SetCoordinate(QPointF p);
	void SetValue(int v);

	QPointF GetCoordinate() const;
	float GetX() const;
	float GetY() const;
	int GetValue() const;

	bool operator==(Node node) const;
};

