#include "Tema4.h"

#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>

Tema4::Tema4(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	ui.mainToolBar->deleteLater();
	this->setAcceptDrops(true);
	InitWeightDialog();
}

Tema4::~Tema4()
{}

void Tema4::mousePressEvent(QMouseEvent* event)
{
	std::vector<Node*> nodes = graph.GetNodes();
	bool canCreate = true;
	Node* toSelect = nullptr;
	for (auto node : nodes)
	{
		if (fabs(node->GetX() - event->pos().x()) < 2 * NODE_RADIUS && fabs(node->GetY() - event->pos().y()) < 2 * NODE_RADIUS)
			canCreate = false;
		if (fabs(node->GetX() - event->pos().x()) < NODE_RADIUS && fabs(node->GetY() - event->pos().y()) < NODE_RADIUS)
			toSelect = node;
	}

	if (event->button() == Qt::LeftButton)
	{
		if (canCreate && !toSelect)
		{
			graph.AddNode(event->pos());
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
				std::vector<Edge*> edges = graph.GetEdges();
				for (auto edge : edges)
				{
					auto firstNode = edge->GetFirstNode();
					auto secondNode = edge->GetSecondNode();
					if (firstNode == selectedNode && secondNode == toSelect ||
						firstNode == toSelect && secondNode == selectedNode)
					{
						return;
					}
				}

				weightDialog->exec();
				graph.AddEdge(selectedNode, toSelect, currentWeight);
				selectedNode = nullptr;
			}
		}
	}
	update();
}

void Tema4::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	QPen pen;
	pen.setWidth(2);
	pen.setBrush(Qt::black);
	painter.setPen(pen);
	auto font = QFont();
	font.setBold(true);
	painter.setFont(font);
	
	std::vector<Node*> nodes = graph.GetNodes();
	for (auto node : nodes)
	{
		if (selectedNode == node) pen.setColor(Qt::red);
		painter.setPen(pen);

		QRect r(node->GetX() - NODE_RADIUS, node->GetY() - NODE_RADIUS, 2 * NODE_RADIUS, 2 * NODE_RADIUS);
		painter.drawEllipse(r);
		QString s;
		s.setNum(node->GetValue());
		painter.drawText(r, Qt::AlignCenter, s);
		
		pen.setColor(Qt::black);
		painter.setPen(pen);
	}

	std::vector<Edge*> edges = graph.GetEdges();
	for (auto edge : edges)
	{
		QPoint firstNode(edge->GetFirstNode()->GetCoordinate());
		QPoint secondNode(edge->GetSecondNode()->GetCoordinate());
		QPointF firstNodeOffset = PointTranslation(firstNode, secondNode);

		double angle = atan2(firstNode.y() - secondNode.y(), firstNode.x() - secondNode.x());
		
		QPointF weightPoint = (firstNode + secondNode) / 2.0f;

		QTransform transform;
		transform.translate(weightPoint.x(), weightPoint.y());
		transform.rotate(180 + qRadiansToDegrees(angle));
		transform.translate(-weightPoint.x(), -weightPoint.y());
		painter.setTransform(transform);
		pen.setColor(Qt::red);
		painter.setPen(pen);
		font.setPixelSize(15);
		painter.setFont(font);
		painter.drawText(weightPoint + QPoint(-10, -10), QString::number(edge->GetWeight()));

		painter.setTransform(QTransform());
		
		pen.setColor(Qt::black);
		for (auto selectedEdge : selectedEdges)
		{
			if (edge == selectedEdge) pen.setColor(Qt::red);
		}
		painter.setPen(pen);
		painter.drawLine(firstNode + firstNodeOffset, secondNode - firstNodeOffset);

	}
}

void Tema4::dragEnterEvent(QDragEnterEvent* event)
{
	event->acceptProposedAction();
}

void Tema4::dropEvent(QDropEvent* event)
{
	auto nodes = graph.GetNodes();
	for (auto node : nodes)
	{
		if (node == selectedNode)
			continue;
		if (fabs(node->GetX() - event->pos().x()) < 2 * NODE_RADIUS && fabs(node->GetY() - event->pos().y()) < 2 * NODE_RADIUS)
			return;
	}
	selectedNode->SetCoordinate(event->pos());
}

void Tema4::InitWeightDialog()
{
	weightDialog = new QDialog();
	QGridLayout* layout = new QGridLayout();

	QLineEdit* lineEdit = new QLineEdit(weightDialog);
	QPushButton* okButton = new QPushButton("Confirm", weightDialog);

	layout->addWidget(lineEdit);
	layout->addWidget(okButton);
	weightDialog->setLayout(layout);

	connect(okButton, &QPushButton::clicked, [=]() {
			currentWeight = lineEdit->displayText().toInt();
			lineEdit->setText("");
			weightDialog->close();
			});
}

void Tema4::on_kruskal_pressed()
{
	selectedEdges = graph.KruskalTree();
	update();
}

void Tema4::on_boruvka_pressed()
{
	selectedEdges = graph.BoruvkaTree();
	update();

}

void Tema4::on_reset_pressed()
{
	graph.Reset();
	update();
}

void Tema4::on_unhighlight_pressed()
{
	selectedEdges.clear();
	update();
}

QPointF Tema4::PointTranslation(QPoint firstNode, QPoint secondNode)
{
	double slope = CalculateSlope(firstNode, secondNode);

	return firstNode.x() < secondNode.x()
		? QPointF{ NODE_RADIUS * cos(atan(slope)), -NODE_RADIUS * sin(atan(slope)) }
	: QPointF{ -NODE_RADIUS * cos(atan(slope)), NODE_RADIUS * sin(atan(slope)) };
}

double Tema4::CalculateSlope(QPoint firstNode, QPoint secondNode)
{
    return (double)-(firstNode.y() - secondNode.y()) / (firstNode.x() - secondNode.x());
}
