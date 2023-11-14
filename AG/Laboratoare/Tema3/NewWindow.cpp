#pragma once

#include "NewWindow.h"
#include <QPaintEvent>


void NewWindow::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	std::vector<Node*> nodes = m_graph->getNodes();
	for (auto node : nodes)
	{
	QPen pen;

		painter.setPen(pen);

		QRect r(node->getX() - NODE_RADIUS, node->getY() - NODE_RADIUS, 2 * NODE_RADIUS, 2 * NODE_RADIUS);
		painter.drawEllipse(r);
		QString s;
		s.setNum(node->getValue());
		painter.drawText(r, Qt::AlignCenter, s);
	}

	std::vector<Edge*> edges = m_graph->getEdges();
	for (auto edge : edges)
	{
		painter.setPen(nullptr);
		QPoint firstNode(edge->getFirstNode()->getCoordinate());
		QPoint secondNode(edge->getSecondNode()->getCoordinate());
		QPointF firstNodeOffset = pointTranslation(firstNode, secondNode);

		double slope = (double)-(firstNode.y() - secondNode.y()) / (firstNode.x() - secondNode.x());
		double angle = atan(slope) * 180 / 3.14;
		if (firstNode.x() < secondNode.x()) angle -= 180;

		QLineF angleline;
		angleline.setP1(secondNode - firstNodeOffset);
		angleline.setLength(NODE_RADIUS);

		angleline.setAngle(angle - 30);
		painter.drawLine(angleline);
		angleline.setAngle(angle + 30);
		painter.drawLine(angleline);

		painter.drawLine(firstNode + firstNodeOffset, secondNode - firstNodeOffset);
	}
}

NewWindow::NewWindow(Graph* graph)
	: m_graph(graph)
{

}

QPointF NewWindow::pointTranslation(QPoint firstNode, QPoint secondNode)
{
	double slope = calculateSlope(firstNode, secondNode);

	return firstNode.x() < secondNode.x()
		? QPointF{NODE_RADIUS* cos(atan(slope)), -NODE_RADIUS * sin(atan(slope))}
	: QPointF{ -NODE_RADIUS * cos(atan(slope)), NODE_RADIUS * sin(atan(slope)) };
}

double NewWindow::calculateSlope(QPoint firstNode, QPoint secondNode)
{
	return (double)-(firstNode.y() - secondNode.y()) / (firstNode.x() - secondNode.x());
}