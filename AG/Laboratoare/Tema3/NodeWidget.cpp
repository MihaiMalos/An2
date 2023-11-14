#include "NodeWidget.h"
#include <QPainter>

NodeWidget::NodeWidget(QWidget* parent /*= nullptr*/)
{

}


void NodeWidget::mousePressEvent(QMouseEvent* event)
{

}

void NodeWidget::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);
	QPainter painter(this);
	QColor penColor = "#ffffff";


}
