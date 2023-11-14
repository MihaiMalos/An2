#pragma once

#include <QWidget>
#include "Graph.h"

class NewWindow : public QWidget
{
public:
	NewWindow(Graph* graph);
protected:
	QPointF pointTranslation(QPoint firstNode, QPoint secondNode);
	double calculateSlope(QPoint firstNode, QPoint secondNode);
	void paintEvent(QPaintEvent* event);

private:
	Graph* m_graph;
	const int NODE_RADIUS = 20;
};