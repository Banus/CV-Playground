#include "glwidget.h"

#include <QtGui/QtEvents>
#include <qmath.h>

#include <GL/glu.h>


GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(QGLFormat(QGL::SampleBuffers), parent),
  fov(45.0) {
    setFocusPolicy(Qt::StrongFocus);
}

QSize GLWidget::minimumSizeHint() const
{
    return QSize(100, 100);
}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void GLWidget::initializeGL()
{
    qglClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    build_geometry();
}

void setUpCamera(double fov, double aspectRatio)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(fov, aspectRatio, 1.0, 1000.0);

    glMatrixMode(GL_MODELVIEW);
}

void GLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);

    setUpCamera(fov, width / (float) height);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    panorama.draw();
}

static QVector3D sphere_point(QPoint const& screenPoint)
{
    GLdouble model[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, model);
    GLdouble proj[16];
    glGetDoublev(GL_PROJECTION_MATRIX, proj);
    GLint view[4];
    glGetIntegerv(GL_VIEWPORT, view);

    double point_x, point_y, point_z;
    gluUnProject(screenPoint.x(), screenPoint.y(), 0.0, model, proj, view,
                 &point_x, &point_y, &point_z);

    QVector3D result(point_x, point_y, point_z);
    result.normalize();

    return result;
}

void GLWidget::mousePressEvent(QMouseEvent * event)
{
    euler_ball.mousePressed(sphere_point(event->pos()));
}

void GLWidget::mouseMoveEvent(QMouseEvent * event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        euler_ball.mouseDragged(sphere_point(event->pos()));
        AngleAxis rotation = euler_ball.getRotation();
        panorama.rotate(180.0 * rotation.angle / M_PI, rotation.axis);
    }

    updateGL();
}

void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Up:
            fov *= 0.9;
            break;
        case Qt::Key_Down:
            fov *= 1.1;
            break;
        case Qt::Key_Escape:
            exit(0);
        default:
            QWidget::keyPressEvent(event);
    }

    setUpCamera(fov, width() / (float) height());

    updateGL();
}

void GLWidget::build_geometry()
{
    GLuint texture = bindTexture(QPixmap("panorama.jpg"),
                                 GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    panorama.setContent(buildSphere(25.0, 40, 40));
}
