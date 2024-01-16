#include "Tema6.h"
#include <QMouseEvent>
#include <QInputDialog>
#include <QPainter>

Tema6::Tema6(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	connect(ui.fordFulkerson, &QPushButton::released, this, &Tema6::OnFordRelease);

	lbl_status = new QLabel(this);
	lbl_status->setGeometry(10, 40, 100, 20);

	resize(800, 600);
}

Tema6::~Tema6()
{}

void Tema6::mouseReleaseEvent(QMouseEvent* ev)
{
	minimumCut.clear();

	std::vector<NodePtr> nodes = graph.GetNodes();
	if (ev->button() == Qt::RightButton)
	{
		NodePtr n = std::make_shared<Node>(ev->position());
		for (auto& on : nodes) {
			if (Node::GetDistance(on->GetCoord(), n->GetCoord()) < 2 * nodeRadius)
				return;
		}

		n->SetInfo(graph.GetNumberOfNodes());
		graph.AddNode(n);
		update();
	}
	else if (ev->button() == Qt::LeftButton)
	{
		NodePtr selected = nullptr;
		for (auto& node : nodes)
		{
			if (Node::GetDistance(ev->position(), node->GetCoord()) <= 2 * nodeRadius)
			{
				selected = node;
				break;
			}
		}

		if (selected)
		{
			if (!isFirstNode)
			{
				firstNode = selected;
				isFirstNode = true;

				lbl_status->setText("Nod " + QString::number(firstNode->GetInfo()) + " selectat");
				lbl_status->setStyleSheet("color:black;");
			}
			else
			{
				if (firstNode != selected) {

					std::string message1 = "Enter capacity of edge " + std::to_string(firstNode->GetInfo()) + std::string(" -> ") + std::to_string(selected->GetInfo());
					std::string message2 = "Enter capacity of edge " + std::to_string(selected->GetInfo()) + std::string(" -> ") + std::to_string(firstNode->GetInfo());
					int cfs = QInputDialog::getInt(this, "Enter capacity", QString::fromStdString(message1));
					int csf = QInputDialog::getInt(this, "Enter capacity", QString::fromStdString(message2));

					graph.AddEdge(Edge(firstNode, selected, cfs, csf));
					isFirstNode = false;
					update();
				}
				else
				{
					isFirstNode = false;
				}

				lbl_status->setText("");
			}
		}
		else
		{
			isFirstNode = false;

			lbl_status->setText("");
		}
	}
}

void Tema6::paintEvent(QPaintEvent* )
{
	QPainter p(this);

	std::vector<std::shared_ptr<Node>> nodes = graph.GetNodes();
	for (auto& node : nodes)
	{
		QPointF coord = node->GetCoord();
		QRect r(coord.x() - nodeRadius, coord.y() - nodeRadius,
			2 * nodeRadius, 2 * nodeRadius);
		p.drawEllipse(r);
		QString num = QString::number(node->GetInfo());
		p.drawText(r, Qt::AlignCenter, num);
	}


	std::vector<Edge> edges = graph.GetEdges();
	for (Edge& edge : edges)
	{
		QLineF lineEdge = QLineF(edge.getFirstNodePtr()->GetCoord(), edge.getSecondNodePtr()->GetCoord());
		ModifyLineLength(lineEdge);

		QPointF middlePoint = { lineEdge.p1().x() + lineEdge.p2().x(), lineEdge.p1().y() + lineEdge.p2().y() };
		middlePoint = { middlePoint.x() * 0.5f, middlePoint.y() * 0.5f };

		if (std::find(minimumCut.begin(), minimumCut.end(), std::pair<int, int>{edge.getFirstNodePtr()->GetInfo(), edge.getSecondNodePtr()->GetInfo()}) != minimumCut.end())
			p.setPen(QColor(255, 0, 0));

		p.drawLine(lineEdge);
		p.setPen(QColor(0, 0, 0));

		if (edge.getCapacity().first) {
			p.setPen(QColor(255, 0, 255));
			QLineF left = QLineF(lineEdge.p2(), lineEdge.p1());
			left.setLength(15);
			left.setAngle(lineEdge.angle() + 195);
			p.drawLine(left);

			QLineF right = QLineF(lineEdge.p2(), lineEdge.p1());
			right.setLength(15);
			right.setAngle(lineEdge.angle() + 165);
			p.drawLine(right);
			p.setPen(QColor(0, 0, 0));
		}

		lineEdge = QLineF(lineEdge.p2(), lineEdge.p1());

		if (edge.getCapacity().second) {
			p.setPen(QColor(0, 0, 255));
			QLineF left = QLineF(lineEdge.p2(), lineEdge.p1());
			left.setLength(15);
			left.setAngle(lineEdge.angle() + 195);
			p.drawLine(left);

			QLineF right = QLineF(lineEdge.p2(), lineEdge.p1());
			right.setLength(15);
			right.setAngle(lineEdge.angle() + 165);
			p.drawLine(right);
			p.setPen(QColor(0, 0, 0));
		}

		QString msg;
		if (edge.getCapacity().first)
			msg += QString("M:") + QString::fromStdString(std::to_string(edge.getCapacity().first)) + " ";

		if (edge.getCapacity().second)
			msg += QString("B:") + QString::fromStdString(std::to_string(edge.getCapacity().second));

		p.drawText(middlePoint, msg);
	}
}

void Tema6::ModifyLineLength(QLineF& line)
{
	float size = line.length();
	size -= nodeRadius;
	line.setLength(size);

	line = QLineF(line.p2(), line.p1());

	size = line.length();
	size -= nodeRadius;
	line.setLength(size);

	line = QLineF(line.p2(), line.p1());
}

void Tema6::OnFordRelease()
{
	auto result = graph.MaximumFlow(0, graph.GetNumberOfNodes() - 1);
	minimumCut = result.second;
	lbl_status->setText(QString("Maximum flow :") + QString::fromStdString(std::to_string(result.first)));

	update();
}