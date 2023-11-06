#include <fstream>

#include "Tema2.h"

Tema2::Tema2(QWidget *parent)
    : QMainWindow(parent)
{
	resize(QSize(900, 900));
	std::ifstream fin("input.txt");
	std::vector<std::vector<int>> matrix;
	int rows, columns;
	fin >> rows >> columns;
	matrix.resize(rows);
	for (int rowIndex = 0; rowIndex < rows; rowIndex++)
	{
		matrix[rowIndex].resize(columns);
		for (int columnIndex = 0; columnIndex < columns; columnIndex++)
			fin >> matrix[rowIndex][columnIndex];
	}
	mazeGraph = new Graph(matrix, EDirection::rightTop);
	mazeGraph->initGraph(size());

		
}

Tema2::~Tema2()
{}

void Tema2::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	painter.setRenderHint(QPainter::Antialiasing);

	auto nodes = mazeGraph->getNodes();
	int nodeRadius = mazeGraph->getRadius();
	for (auto node = nodes.begin(); node != nodes.end(); node++)
	{
		QRectF r(node->second->getX() - nodeRadius, node->second->getY() - nodeRadius, 2 * nodeRadius, 2 * nodeRadius);
		painter.drawEllipse(r);

		QRectF r2(node->second->getX() - nodeRadius, node->second->getY() - nodeRadius + height()/2.0f, 2 * nodeRadius, 2 * nodeRadius);
		painter.drawEllipse(r2);
	}

		std::vector<Edge*> edges = mazeGraph->getEdges();
	for (auto edge : edges)
	{
		QPointF firstNode(edge->getFirstNode()->getCoordinate());
		QPointF secondNode(edge->getSecondNode()->getCoordinate());
		QPointF firstNodeOffset = pointTranslation(firstNode, secondNode);

		double slope = (double)-(firstNode.y() - secondNode.y()) / (firstNode.x() - secondNode.x());
		double angle = atan(slope) * 180 / 3.14;
		if (firstNode.x() < secondNode.x()) angle -= 180;

		painter.drawLine(firstNode + firstNodeOffset, secondNode - firstNodeOffset);
		painter.drawLine(firstNode + firstNodeOffset + QPointF(0, height()/2.0f), secondNode - firstNodeOffset + QPointF(0, height() / 2.0f));

	}

	auto matrix = mazeGraph->getMatrix();
	int matrixRows = matrix.size();
	int matrixCols = matrix[0].size();

	// Calculate the starting point for drawing
	float rectWidth = (float) width() / matrixCols / 2.1f;
	float rectHeight = (float) height() / matrixRows / 2.1f;

	// Draw squares for each matrix element
	for (int row = 0; row < matrixRows; ++row) {
		for (int column = 0; column < matrixCols; ++column) {
			int value = matrix[row][column];
			QColor rectColor;
			switch (value)
			{
			case 0:
				rectColor = Qt::black;
				break;
			case 1:
				rectColor = Qt::white;
				break;
			case 2:
				rectColor = Qt::red;
				break;
			case 3:
				rectColor = Qt::blue;
				break;
			}
			QRectF r3(width() / matrixCols * 0.07f + column * rectWidth,
				      height() / matrixRows * 0.07f + row * rectHeight, 
				      rectWidth, rectHeight);

			painter.fillRect(r3, rectColor);
		}
	}


	// Calculate the center of the widget
	float centerX = width() / 2.0f;
	float centerY = height() / 2.0f;
	// Draw horizontal line
	painter.drawLine(0, centerY, width(), centerY);
	// Draw vertical line
	painter.drawLine(centerX, 0, centerX, height());
}

void Tema2::resizeEvent(QResizeEvent* event)
{
	mazeGraph->updateSize(event->size());
}
QPointF Tema2::pointTranslation(QPointF firstNode, QPointF secondNode)
{
	double slope = calculateSlope(firstNode, secondNode);
	double radius = mazeGraph->getRadius();

	return firstNode.x() < secondNode.x()
		? QPointF{radius * cos(atan(slope)), -radius * sin(atan(slope))}
	: QPointF{ -radius * cos(atan(slope)), radius * sin(atan(slope)) };
}

double Tema2::calculateSlope(QPointF firstNode, QPointF secondNode)
{
	return (double)-(firstNode.y() - secondNode.y()) / (firstNode.x() - secondNode.x());
}