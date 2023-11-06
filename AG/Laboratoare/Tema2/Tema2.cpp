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
	mazeGraph = new Graph(matrix);
	mazeGraph->InitGraph(size());
		
}

Tema2::~Tema2()
{}

void Tema2::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	// Nodes paint
	auto nodes = mazeGraph->GetNodes();
	int nodeRadius = mazeGraph->GetRadius();

	for (auto node = nodes.begin(); node != nodes.end(); node++)
	{
		auto nodeCoords = node->second->GetCoordinate();
		QRectF r(nodeCoords.x() - nodeRadius, nodeCoords.y() - nodeRadius, 2 * nodeRadius, 2 * nodeRadius);
		painter.drawEllipse(r);

		QRectF r2(nodeCoords.x() - nodeRadius, nodeCoords.y() - nodeRadius + height() / 2.0f, 2 * nodeRadius, 2 * nodeRadius);
		painter.drawEllipse(r2);
	}

	// Path nodes
	for (auto node : mazeGraph->ComputeMazePaths())
	{
		painter.setBrush(Qt::green);
		auto nodeCoords = node->GetCoordinate();

		QRectF r2(nodeCoords.x() - nodeRadius, nodeCoords.y() - nodeRadius + height() / 2.0f, 2 * nodeRadius, 2 * nodeRadius);
		painter.drawEllipse(r2);
	}

	// Entry node
	{
		painter.setBrush(Qt::blue);
		auto nodeCoords = mazeGraph->GetEntryNode()->GetCoordinate();

		QRectF r(nodeCoords.x() - nodeRadius, nodeCoords.y() - nodeRadius, 2 * nodeRadius, 2 * nodeRadius);
		painter.drawEllipse(r);

		QRectF r2(nodeCoords.x() - nodeRadius, nodeCoords.y() - nodeRadius + height() / 2.0f, 2 * nodeRadius, 2 * nodeRadius);
		painter.drawEllipse(r2);
	}

	// Exit nodes
	for (auto node : mazeGraph->GetExitNodes())
	{
		painter.setBrush(Qt::red);
		auto nodeCoords = node->GetCoordinate();

		QRectF r(nodeCoords.x() - nodeRadius, nodeCoords.y() - nodeRadius, 2 * nodeRadius, 2 * nodeRadius);
		painter.drawEllipse(r);

		QRectF r2(nodeCoords.x() - nodeRadius, nodeCoords.y() - nodeRadius + height() / 2.0f, 2 * nodeRadius, 2 * nodeRadius);
		painter.drawEllipse(r2);
	}

	// Edges paint
	std::vector<Edge*> edges = mazeGraph->GetEdges();

	for (auto edge : edges)
	{
		QPointF firstNode(edge->GetFirstNode()->GetCoordinate());
		QPointF secondNode(edge->GetSecondNode()->GetCoordinate());
		QPointF firstNodeOffset = pointTranslation(firstNode, secondNode);

		double slope = (double)-(firstNode.y() - secondNode.y()) / (firstNode.x() - secondNode.x());
		double angle = atan(slope) * 180 / 3.14;
		if (firstNode.x() < secondNode.x()) angle -= 180;

		painter.drawLine(firstNode + firstNodeOffset, secondNode - firstNodeOffset);
		painter.drawLine(firstNode + firstNodeOffset + QPointF(0, height()/2.0f), secondNode - firstNodeOffset + QPointF(0, height() / 2.0f));

	}

	// Matrix paint


	auto matrix = mazeGraph->GetMatrix();
	int matrixRows = matrix.size();
	int matrixCols = matrix[0].size();

	float rectWidth = (float) width() / matrixCols / 2.1f;
	float rectHeight = (float) height() / matrixRows / 2.1f;

	for (int row = 0; row < matrixRows; ++row) {
		for (int column = 0; column < matrixCols; ++column) {

			int value = matrix[row][column];
			QColor rectColor;

			if (value == 0) rectColor = Qt::black;
			else if (value == 1) rectColor = Qt::transparent;
			else if (value == 2) rectColor = Qt::red;
			else if (value == 3) rectColor = Qt::blue;


			QRectF r3(width() / matrixCols * 0.07f + column * rectWidth,
				      height() / matrixRows * 0.07f + row * rectHeight, 
				      rectWidth, rectHeight);

			QRectF r4(width() / matrixCols * 0.07f + column * rectWidth,
				height() / matrixRows * 0.07f + row * rectHeight + height() / 2.0f,
				rectWidth, rectHeight);

			painter.fillRect(r3, rectColor);

			for (auto node : mazeGraph->ComputeMazePaths())
			{
				int key = row * matrixCols + column;
				auto it = nodes.find(key);
				if (it != nodes.end() && node == it->second)
				{
					painter.fillRect(r4, Qt::green);
					break;
				}
			}
			painter.fillRect(r4, rectColor);
			
		}
	}


	// Screen divider in 4 squares

	float centerX = width() / 2.0f;
	float centerY = height() / 2.0f;
	painter.drawLine(0, centerY, width(), centerY);
	painter.drawLine(centerX, 0, centerX, height());
}

void Tema2::resizeEvent(QResizeEvent* event)
{
	mazeGraph->UpdateSize(event->size());
}
QPointF Tema2::pointTranslation(QPointF firstNode, QPointF secondNode)
{
	double slope = calculateSlope(firstNode, secondNode);
	double radius = mazeGraph->GetRadius();

	return firstNode.x() < secondNode.x()
		? QPointF{radius * cos(atan(slope)), -radius * sin(atan(slope))}
	: QPointF{ -radius * cos(atan(slope)), radius * sin(atan(slope)) };
}

double Tema2::calculateSlope(QPointF firstNode, QPointF secondNode)
{
	return (double)-(firstNode.y() - secondNode.y()) / (firstNode.x() - secondNode.x());
}