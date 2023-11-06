#pragma once

#include <QtWidgets/QMainWindow>
#include <QPaintEvent>
#include <QResizeEvent>

#include "Graph.h"


class Tema2 : public QMainWindow
{
    Q_OBJECT

public:
    Tema2(QWidget *parent = nullptr);
    ~Tema2();

protected:
    void paintEvent(QPaintEvent* event);
    void resizeEvent(QResizeEvent* event);

private:
    QPointF pointTranslation(QPointF firstNode, QPointF secondNode);
    double calculateSlope(QPointF firstNode, QPointF secondNode);
    Graph* mazeGraph;
};
