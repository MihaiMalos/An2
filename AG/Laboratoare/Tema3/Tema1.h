#pragma once

#include <QtWidgets/QMainWindow>

#include "ui_Tema1.h"
#include "Graph.h"
#include "NewWindow.h"

class Tema1 : public QMainWindow
{
	Q_OBJECT

public:
	Tema1(QWidget* parent = nullptr);
	~Tema1();

public slots:
	void on_resetGraph_clicked();
	void on_topologicalSort_clicked();
	void on_findRoot_clicked();

protected:
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void paintEvent(QPaintEvent* event);

	virtual void dragEnterEvent(QDragEnterEvent* event);
	virtual void dropEvent(QDropEvent* event);


private:
	const int NODE_RADIUS = 20;
	QPointF pointTranslation(QPoint circleCenter, QPoint point);
	double calculateSlope(QPoint firstNode, QPoint secondNode);

	Ui::Tema1Class ui;
	Graph graph;
	Node* selectedNode = nullptr;
};
