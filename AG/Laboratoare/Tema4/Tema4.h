#pragma once

#include <QtWidgets/QMainWindow>
#include <QDialog>
#include <unordered_set>

#include "Graph.h"
#include "ui_Tema4.h"

class Tema4 : public QMainWindow
{
    Q_OBJECT

public:
    Tema4(QWidget *parent = nullptr);
    ~Tema4();

protected:
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void paintEvent(QPaintEvent* event);

	virtual void dragEnterEvent(QDragEnterEvent* event);
	virtual void dropEvent(QDropEvent* event);

private:
	void InitWeightDialog();

private slots:
	void on_kruskal_pressed();
	void on_boruvka_pressed();
	void on_reset_pressed();
	void on_unhighlight_pressed();



private:
	const int NODE_RADIUS = 20;
	QPointF PointTranslation(QPoint firstNode, QPoint secondNode);
	double CalculateSlope(QPoint firstNode, QPoint secondNode);

	Ui::Tema4Class ui;
	Graph graph;
	Node* selectedNode = nullptr;
	QDialog* weightDialog;
	int currentWeight;
	std::vector<Edge*> selectedEdges;
};
