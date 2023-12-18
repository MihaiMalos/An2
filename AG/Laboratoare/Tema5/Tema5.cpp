#include "Tema5.h"

#include <QMouseEvent>
#include <QFile>
#include <QXmlStreamReader>
#include <limits>

Tema5::Tema5(QWidget *parent)
    : QMainWindow(parent)
	, kRadius{5}
	, m_firstNodeSelected{nullptr}
	, m_secondNodeSelected{nullptr}
	, m_nodesPath{std::vector<Node*>()}
{
	ui.setupUi(this);
	ui.mainToolBar->deleteLater();
	this->setAcceptDrops(true);

	InitMap();
}

Tema5::~Tema5()
{}

void Tema5::mousePressEvent(QMouseEvent* event)
{
	Node* toSelect{nullptr};
	if (event->button() == Qt::MiddleButton)
	{
		m_firstNodeSelected = nullptr;
		m_secondNodeSelected = nullptr;
		m_nodesPath = std::vector<Node*>();
	}
	if (event->button() == Qt::RightButton)
	{
		double minDistance = std::numeric_limits<double>::max();
		for (const auto& node : m_graph.GetNodes())
		{
			QPointF coordinates = node->GetCoordinate();
			ToScreenCoordinates(coordinates);
			if (fabs(coordinates.x() - event->pos().x()) < 5 && fabs(coordinates.y() - event->pos().y()) < 5)
			{
				const auto& currentDistance = EuclideanDistance(coordinates, event->pos());
				if (minDistance > currentDistance)
				{
					minDistance = currentDistance;
					toSelect = node;
				}
			}
		}
		if (!toSelect || m_firstNodeSelected == toSelect) return;

		if (!m_firstNodeSelected)
		{
			m_firstNodeSelected = toSelect;
		}
		else
		{
			m_secondNodeSelected = toSelect;
			m_nodesPath = m_graph.DijkstraPath(m_firstNodeSelected, m_secondNodeSelected);
		}
	}
	update();
}

void Tema5::paintEvent(QPaintEvent* event)
{

	QPainter painter(this);

	for (auto node : m_graph.GetNodes())
	{
		if (m_firstNodeSelected == node || m_secondNodeSelected == node)
		{
			QPointF coordinates(node->GetCoordinate());
			ToScreenCoordinates(coordinates);
			painter.setPen(Qt::red);
			painter.setBrush(Qt::red);
			QRect rect(coordinates.x() - kRadius, coordinates.y() - kRadius, 2 * kRadius, 2 * kRadius);
			painter.drawEllipse(rect);

		}
	}

	painter.setPen(Qt::black);
	for (auto edge : m_graph.GetEdges())
	{
		QPointF firstNode(edge->GetFirstNode()->GetCoordinate());
		QPointF secondNode(edge->GetSecondNode()->GetCoordinate());

		ToScreenCoordinates(firstNode);
		ToScreenCoordinates(secondNode);
		painter.drawLine(firstNode, secondNode);
	}

	if (m_nodesPath.empty()) return;
	QPen pen(Qt::red);
	pen.setWidth(2);
	painter.setPen(pen);
	for (int index = 0; index < m_nodesPath.size() - 1; index++)
	{
		QPointF firstNode = m_nodesPath[index]->GetCoordinate();
		QPointF secondNode = m_nodesPath[index+1]->GetCoordinate();

		ToScreenCoordinates(firstNode);
		ToScreenCoordinates(secondNode);
		painter.drawLine(firstNode, secondNode);
	}
}


void Tema5::InitMap()
{
	QFile file("Harta_Luxemburg.xml");

	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Error: Cannot open file";
		return;
	}

	QXmlStreamReader xml(&file);
	QString nodeString = QString("node");
	QString arcString = QString("arc");

	const auto& lowestValue = std::numeric_limits<int>::min();
	const auto& highestValue = std::numeric_limits<int>::max();
	m_lowerBound = std::move(QPoint(highestValue, highestValue));
	m_upperBound = std::move(QPoint(lowestValue, lowestValue));
	while (!xml.atEnd() && !xml.hasError()) {
		QXmlStreamReader::TokenType token = xml.readNext();

		if (token == QXmlStreamReader::StartElement) {
			
			if (xml.name() == nodeString) {
				const int& longitude = xml.attributes().value("longitude").toInt(); // x
				const int& latitude = xml.attributes().value("latitude").toInt(); // y

				if (m_lowerBound.y() > latitude) m_lowerBound.setY(latitude);
				if (m_upperBound.y() < latitude) m_upperBound.setY(latitude);
				if (m_lowerBound.x() > longitude) m_lowerBound.setX(longitude);
				if (m_upperBound.x() < longitude) m_upperBound.setX(longitude);

				m_graph.AddNode(std::move(QPoint(longitude, latitude)));
			}
			else if (xml.name() == arcString) {
				const int& firstNodeId = xml.attributes().value("from").toInt();
				const int& secondNodeId = xml.attributes().value("to").toInt();
				const int& length = xml.attributes().value("length").toInt();

				Node* firstNode = m_graph.GetNodes().at(firstNodeId);
				Node* secondNode = m_graph.GetNodes().at(secondNodeId);
				m_graph.AddEdge(firstNode, secondNode, length);
			}
		}
	}
	if (xml.hasError()) {
		qDebug() << "Error: " << xml.errorString();
	}

	file.close();
}

void Tema5::ToScreenCoordinates(QPointF& coordinates)
{
	const auto& scaleFactorX = static_cast<double>(width()) / (m_upperBound.x() - m_lowerBound.x());
	const auto& scaleFactorY = static_cast<double>(height()) / (m_upperBound.y() - m_lowerBound.y());

	coordinates.setX((coordinates.x() - m_lowerBound.x()) * scaleFactorX);
	coordinates.setY((m_upperBound.y() - coordinates.y()) * scaleFactorY);
}

double Tema5::EuclideanDistance(const QPointF& point1, const QPointF& point2) {
	double deltaX = point2.x() - point1.x();
	double deltaY = point2.y() - point1.y();

	return std::sqrt(deltaX * deltaX + deltaY * deltaY);
}