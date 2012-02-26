#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui/QMainWindow>

class GLWidget;

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    ~Window();

private:
    GLWidget * glWidget;
};

#endif // WINDOW_H
