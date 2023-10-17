#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_Tema1.h"
#include "Graph.h"

class Tema1 : public QMainWindow
{
	Q_OBJECT

public:
	Tema1(QWidget* parent = nullptr);
	~Tema1();

	virtual void mousePressEvent(QMouseEvent* event);
	virtual void paintEvent(QPaintEvent* event);

private:
	const int NODE_RADIUS = 40;
	QPointF pointTranslation(QPoint circleCenter, QPoint point);
	Ui::Tema1Class ui;
	Graph graph;
	Node* selectedNode = nullptr;
};
