#pragma once

#include <QtWidgets/QMainWindow>
#include "Graph.h"

#include "ui_Tema5.h"

class Tema5 : public QMainWindow
{
    Q_OBJECT

public:
    Tema5(QWidget *parent = nullptr);
    ~Tema5();

protected:
	virtual void mousePressEvent(QMouseEvent* event);
	virtual void paintEvent(QPaintEvent* event);

private:
	void InitMap();
	void ToScreenCoordinates(QPointF& coordinates);

private:
	Ui::Tema5Class ui;
	Graph m_graph;
	Node* m_selectedNode = nullptr;
	QPoint m_lowerBound, m_upperBound;
};