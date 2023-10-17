#include "Tema1.h"

#include <QMouseEvent>

Tema1::Tema1(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.mainToolBar->deleteLater();
	graph.setOrientation(false);
}

Tema1::~Tema1()
{}

void Tema1::mousePressEvent(QMouseEvent* event)
{
	std::vector<Node*> nodes = graph.getNodes();
	if (event->button() == Qt::LeftButton)
	{
		for (auto node : nodes)
		{
			if (fabs(node->getX() - event->pos().x()) < 2*NODE_RADIUS && fabs(node->getY() - event->pos().y()) < 2*NODE_RADIUS)
				return;
		}
		graph.addNode(event->pos());
		graph.save("output.txt");
		update();
	}
	else if (event->button() == Qt::RightButton)
	{
		for (auto node : nodes)
		{
			if (fabs(node->getX() - event->pos().x()) < NODE_RADIUS && fabs(node->getY() - event->pos().y()) < NODE_RADIUS)
			{
				if (selectedNode == nullptr)
				{
					selectedNode = node;
				}
				else if (selectedNode == node)
				{
					return;
				}
				else
				{
					std::vector<Edge*> edges = graph.getEdges();
					for (auto edge : edges)
					{
						auto firstNode = edge->getFirstNode();
						auto secondNode = edge->getSecondNode();
						if (firstNode == selectedNode && secondNode == node || 
							firstNode == node && secondNode == selectedNode && !graph.isOrientated())
						{
							return;
						}
					}

					graph.addEdge(selectedNode, node);
					graph.save("output.txt");
					update();
					selectedNode = nullptr;
				}
				break;


			}
		}
	}
}



void Tema1::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	std::vector<Node*> nodes = graph.getNodes();
	for (auto node : nodes)
	{
		QRect r(node->getX() - NODE_RADIUS, node->getY() - NODE_RADIUS, 2*NODE_RADIUS, 2*NODE_RADIUS);
		painter.drawEllipse(r);
		QString s;
		s.setNum(node->getValue());

		painter.drawText(r, Qt::AlignCenter, s);
	}
	std::vector<Edge*> edges = graph.getEdges();
	for (auto edge : edges)
	{
		QPoint firstNode(edge->getFirstNode()->getCoordinate());
		QPoint secondNode(edge->getSecondNode()->getCoordinate());
		QPointF firstNodeOffset = pointTranslation(firstNode, secondNode);
		

		painter.drawLine(firstNode + firstNodeOffset, secondNode - firstNodeOffset);

	}
}

QPointF Tema1::pointTranslation(QPoint firstNode, QPoint secondNode)
{
		if (firstNode.x() == secondNode.x() && firstNode.y() < secondNode.y())
			return { 0, (qreal) NODE_RADIUS };
		else if (firstNode.x() == secondNode.x() && firstNode.y() > secondNode.y())
			return { 0, (qreal) -NODE_RADIUS };
		else if (firstNode.y() == secondNode.y() && firstNode.x() < secondNode.x())
			return { (qreal)NODE_RADIUS, 0 };
		else if (firstNode.y() == secondNode.y() && firstNode.x() > secondNode.x())
			return { (qreal)-NODE_RADIUS, 0 };

		double slope = (double) -(firstNode.y() - secondNode.y()) / (firstNode.x() - secondNode.x());

		return firstNode.x() < secondNode.x() 
			? QPointF{NODE_RADIUS* cos(atan(slope)), -NODE_RADIUS * sin(atan(slope))} 
			: QPointF{ -NODE_RADIUS * cos(atan(slope)), NODE_RADIUS * sin(atan(slope)) };
}
