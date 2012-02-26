#include "window.h"
#include "glwidget.h"

#include <QtGui/QHBoxLayout>

Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    glWidget = new GLWidget;

    setCentralWidget(glWidget);

    setWindowTitle(tr("CV Playground"));
}

Window::~Window()
{

}
