#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Tema5.h"

class Tema5 : public QMainWindow
{
    Q_OBJECT

public:
    Tema5(QWidget *parent = nullptr);
    ~Tema5();

private:
    Ui::Tema5Class ui;
};
