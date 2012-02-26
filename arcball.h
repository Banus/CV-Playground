#ifndef ARCBALL_H
#define ARCBALL_H

#include <QVector3D>
#include <QQuaternion>

struct AngleAxis
{
    double angle;
    QVector3D axis;

    AngleAxis(double angle, QVector3D const& axis) :
        angle(angle), axis(axis) {}

    AngleAxis(QQuaternion const& rotation);
};

class ArcBall {

public:
  ArcBall(float center_x = 0.0, float center_y = 0.0, float radius = 1.0);

  void resize(float center_x, float center_y, float radius);

  void mousePressed(int mouseX, int mouseY);
  void mouseDragged(int mouseX, int mouseY);

  AngleAxis getRotation() const;
  void setRotation(AngleAxis const& rotation);

private:
  float center_x, center_y, radius;
  QVector3D v_down, v_drag;
  QQuaternion q_now, q_down;

  QVector3D mouse_to_sphere(float x, float y);
};

class EulerBall
{
public:
    EulerBall() {}

    void mousePressed(QVector3D const& startPoint);
    void mouseDragged(QVector3D const& currentPoint);

    AngleAxis getRotation() const;

 private:
    double phi_down, theta_down;
    double phi_now, theta_now;
    QVector3D v_down;
};

#endif // ARCBALL_H
