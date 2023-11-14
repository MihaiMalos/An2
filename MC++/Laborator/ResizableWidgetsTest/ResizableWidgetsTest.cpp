#include "ResizableWidgetsTest.h"
#include <QLabel>
#include <QGridLayout>

ResizableWidgetsTest::ResizableWidgetsTest(QWidget *parent)
    : QMainWindow(parent)
{
    //ui.setupUi(this);
    QGridLayout* layout = new QGridLayout(this);
    layout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    label = new QLabel("Salut", this);
    layout->addWidget(label, 0, 0, Qt::AlignCenter);
    this->setLayout(layout);
}

ResizableWidgetsTest::~ResizableWidgetsTest()
{}

void ResizableWidgetsTest::resizeEvent(QResizeEvent* event)
{
	int fontSize = width() / 20;

	// Set the font size for the text label
    QFont font = label->font();
	font.setPointSize(fontSize);
	label->setFont(font);
}
