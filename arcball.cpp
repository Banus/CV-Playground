#include "arcball.h"

#include <qmath.h>

static const QQuaternion angleAxisRotation(float angle, QVector3D const& axis) {

    return QQuaternion(cos(angle / 2.0f), axis * sin(angle / 2.0f));
}

AngleAxis::AngleAxis(QQuaternion const& rotation)
{
    float scale = sqrt(rotation.x() * rotation.x() +
                       rotation.y() * rotation.y() +
                       rotation.z() * rotation.z());

    float invscale;
    if (scale == 0.0f)
        invscale = 1.0f;
    else
        invscale = 1 / scale;

    angle = 2.0f * acos(rotation.scalar() / rotation.length() );
    axis.setX(rotation.x() * invscale);
    axis.setY(rotation.y() * invscale);
    axis.setZ(rotation.z() * invscale);
}

ArcBall::ArcBall(float center_x, float center_y, float radius) :
        center_x(center_x),
        center_y(center_y),
        radius(radius) {}

void ArcBall::resize(float center_x, float center_y, float radius)
{
    this->center_x = center_x;
    this->center_y = center_y;
    this->radius = radius;
}

void ArcBall::mousePressed(int mouseX, int mouseY) {

    v_down = mouse_to_sphere(mouseX, mouseY);
    q_down = q_now;
}

void ArcBall::mouseDragged(int mouseX, int mouseY) {

    v_drag = mouse_to_sphere(mouseX, mouseY);
    QQuaternion q_drag( QVector3D::dotProduct(v_down, v_drag),
                        QVector3D::crossProduct(v_down, v_drag));
    q_now = q_drag * q_down;
}

AngleAxis ArcBall::getRotation() const {

    return AngleAxis(q_now);
}

void ArcBall::setRotation(AngleAxis const& rotation) {

    q_now = angleAxisRotation(rotation.angle, rotation.axis);
    q_down = q_now;
}

QVector3D ArcBall::mouse_to_sphere(float x, float y) {

    QVector3D v((x - center_x) / radius, (center_y - y) / radius, 0.0f);

    float mag = v.x() * v.x() + v.y() * v.y();
    if (mag > 1.0f)
        v.normalize();
    else
        v.setZ(sqrt(1.0f - mag));

    return v;
}

void EulerBall::mousePressed(const QVector3D &startPoint)
{
    phi_down = phi_now;
    theta_down = theta_now;

    v_down = startPoint;
}

void EulerBall::mouseDragged(const QVector3D &currentPoint)
{
    QVector3D delta = currentPoint - v_down;

    phi_now = phi_down - 2.0 * atan(delta.x() / 2.0);
    theta_now = theta_down - 2.0 * atan(delta.y() / 2.0);
}

AngleAxis EulerBall::getRotation() const
{
    QQuaternion xRotation = QQuaternion::
            fromAxisAndAngle(QVector3D(0.0, 1.0, 0.0), 180 * phi_now / M_PI);
    QQuaternion yRotation = QQuaternion::
            fromAxisAndAngle(QVector3D(1.0, 0.0, 0.0), 180 * theta_now / M_PI);

    return AngleAxis(yRotation * xRotation);
}
