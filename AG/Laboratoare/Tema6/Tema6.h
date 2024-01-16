#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Tema6.h"
#include <QLabel>
#include <QPushButton>
#include "graph.h"

class Tema6 : public QMainWindow
{
    Q_OBJECT

public:
    Tema6(QWidget *parent = nullptr);
    ~Tema6();

	void mouseReleaseEvent(QMouseEvent* ev) override;
	void paintEvent(QPaintEvent* p) override;

	void ModifyLineLength(QLineF& line);

public slots:
	void OnFordRelease();

private:
    Ui::Tema6Class ui;
	QLabel* lbl_status;
	Graph graph;

	const float nodeRadius = 15.f;
	bool isFirstNode = false;
	NodePtr firstNode;
	std::vector<std::pair<int, int>> minimumCut;
};
