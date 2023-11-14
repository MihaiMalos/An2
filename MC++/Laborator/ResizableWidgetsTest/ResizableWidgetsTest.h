#pragma once

#include <QtWidgets/QMainWindow>
#include <QLabel>
//#include "ui_ResizableWidgetsTest.h"

class ResizableWidgetsTest : public QMainWindow
{
    Q_OBJECT

public:
    ResizableWidgetsTest(QWidget *parent = nullptr);
    ~ResizableWidgetsTest();

    void resizeEvent(QResizeEvent* event) override;

private:
    QLabel* label;
    //Ui::ResizableWidgetsTestClass ui;
};
