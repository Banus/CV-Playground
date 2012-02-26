#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

#include "geometry.h"
#include "arcball.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

signals:

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent * event);

    void keyPressEvent(QKeyEvent * event);

private:
    void build_geometry();

    Mesh sphere;
    EulerBall euler_ball;
    double fov;
};

#endif // GLWIDGET_H
