#pragma once

#include <QPainter>

class Node
{
	int value;
	QPoint coordinate;

public:
	Node(QPoint p);
	Node(const Node& node);

	void SetCoordinate(QPoint p);
	void SetValue(int v);

	QPoint GetCoordinate() const;
	int GetX() const;
	int GetY() const;
	int GetValue() const;

	bool operator==(Node node) const;
};

