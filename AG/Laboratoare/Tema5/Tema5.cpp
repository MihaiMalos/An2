#include "Tema5.h"

#include <QMouseEvent>
#include <QFile>
#include <QXmlStreamReader>
#include <limits>

Tema5::Tema5(QWidget *parent)
    : QMainWindow(parent)
{
	ui.setupUi(this);
	ui.mainToolBar->deleteLater();
	this->setAcceptDrops(true);

	InitMap();
	qDebug() << m_lowerBound << m_upperBound;
	qDebug() << width() << height();
}

Tema5::~Tema5()
{}

void Tema5::mousePressEvent(QMouseEvent* event)
{

	update();
}

void Tema5::paintEvent(QPaintEvent* event)
{

	QPainter painter(this);
	painter.setPen(Qt::black);

	std::vector<Edge*> edges = m_graph.GetEdges();
	for (auto edge : edges)
	{
		QPointF firstNode(edge->GetFirstNode()->GetCoordinate());
		QPointF secondNode(edge->GetSecondNode()->GetCoordinate());

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
	coordinates.setY((coordinates.y() - m_lowerBound.y()) * scaleFactorY);
}
