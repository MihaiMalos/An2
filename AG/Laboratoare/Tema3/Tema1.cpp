#include "Tema1.h"

#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <fstream>

Tema1::Tema1(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.mainToolBar->deleteLater();
	this->setAcceptDrops(true);
	
}

Tema1::~Tema1()
{}


void Tema1::on_resetGraph_clicked()
{
	graph.reset();
	std::ofstream ofs;
	ofs.open("output.txt", std::ofstream::out | std::ofstream::trunc);
	ofs.close();
	update();
}

void Tema1::on_topologicalSort_clicked()
{
	auto predecessors = graph.TopologicSort(0, "output.txt");
	if (predecessors.empty()) return;
	Graph* newGraph = new Graph();

	for (auto node : graph.getNodes())

	{
		newGraph->addNode(node);
	}
	for (int index = 0; index < predecessors.size(); index++)
	{
		auto nodes = newGraph->getNodes();
		if (predecessors[index] < 0) continue;
		Node* currentNode = nodes[index];
		Node* predecessor = nodes[predecessors[index]];

		newGraph->addEdge(predecessor, currentNode);
	}


	NewWindow* newWindow = new NewWindow(newGraph);
	newWindow->show();



}

void Tema1::on_findRoot_clicked()
{
	graph.FindRoot();
}

void Tema1::mousePressEvent(QMouseEvent* event)
{
	std::vector<Node*> nodes = graph.getNodes();
	bool canCreate = true;
	Node* toSelect = nullptr;
	for (auto node : nodes)
	{
		if (fabs(node->getX() - event->pos().x()) < 2 * NODE_RADIUS && fabs(node->getY() - event->pos().y()) < 2 * NODE_RADIUS)
			canCreate = false;
		if (fabs(node->getX() - event->pos().x()) < NODE_RADIUS && fabs(node->getY() - event->pos().y()) < NODE_RADIUS)
			toSelect = node;
	}

	if (event->button() == Qt::LeftButton)
	{
		if (canCreate && !toSelect)
		{
			graph.addNode(event->pos());
			selectedNode = nullptr;
		}
		else if (!canCreate && toSelect)
		{
			selectedNode = toSelect;
			QDrag* drag = new QDrag(this);
			QMimeData* mimeData = new QMimeData;
			drag->setMimeData(mimeData);
			Qt::DropAction dropAction = drag->exec(Qt::MoveAction);
			selectedNode = nullptr;
		}
	}
	else if (event->button() == Qt::RightButton)
	{
		if (!canCreate && toSelect)
		{
			if (selectedNode == nullptr)
			{
				selectedNode = toSelect;
			}
			else if (selectedNode == toSelect)
			{
				selectedNode = nullptr;
			}
			else
			{
				std::vector<Edge*> edges = graph.getEdges();
				for (auto edge : edges)
				{
					auto firstNode = edge->getFirstNode();
					auto secondNode = edge->getSecondNode();
					if (firstNode == selectedNode && secondNode == toSelect)
					{
						return;
					}
				}

				graph.addEdge(selectedNode, toSelect);
				selectedNode = nullptr;
			}
		}
	}
	update();
}



void Tema1::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	std::vector<Node*> nodes = graph.getNodes();
	for (auto node : nodes)
	{
		QPen pen;
		if (selectedNode == node) pen.setColor(Qt::red);
		painter.setPen(pen);

		QRect r(node->getX() - NODE_RADIUS, node->getY() - NODE_RADIUS, 2*NODE_RADIUS, 2*NODE_RADIUS);
		painter.drawEllipse(r);
		QString s;
		s.setNum(node->getValue());
		painter.drawText(r, Qt::AlignCenter, s);
	}
	std::vector<Edge*> edges = graph.getEdges();
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

void Tema1::dragEnterEvent(QDragEnterEvent* event)
{
	event->acceptProposedAction();
}

void Tema1::dropEvent(QDropEvent* event)
{
	auto nodes = graph.getNodes();
	for (auto node : nodes)
	{
		if (node == selectedNode)
			continue;
		if (fabs(node->getX() - event->pos().x()) < 2 * NODE_RADIUS && fabs(node->getY() - event->pos().y()) < 2 * NODE_RADIUS)
			return;
	}
	selectedNode->setCoordinate(event->pos());
}

QPointF Tema1::pointTranslation(QPoint firstNode, QPoint secondNode)
{
	double slope = calculateSlope(firstNode, secondNode);

		return firstNode.x() < secondNode.x() 
			? QPointF{NODE_RADIUS* cos(atan(slope)), -NODE_RADIUS * sin(atan(slope))} 
			: QPointF{ -NODE_RADIUS * cos(atan(slope)), NODE_RADIUS * sin(atan(slope)) };
}

double Tema1::calculateSlope(QPoint firstNode, QPoint secondNode)
{
	return (double) - (firstNode.y() - secondNode.y()) / (firstNode.x() - secondNode.x());
}
