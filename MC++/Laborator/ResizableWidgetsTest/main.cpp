#include "ResizableWidgetsTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ResizableWidgetsTest w;
    w.show();
    return a.exec();
}
