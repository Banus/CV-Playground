#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QVector3D>
#include <QVector2D>
#include <QMatrix4x4>
#include <QGLWidget>

struct Triangle {
    GLushort v1, v2, v3;

    Triangle(GLushort v1 = 0, GLushort v2 = 0, GLushort v3 = 0) :
        v1(v1), v2(v2), v3(v3) {}
};

struct Mesh
{
    QVector<Triangle> triangles;
    QVector<QVector2D> texCoords;
    QVector<QVector3D> vertices;

    QMatrix4x4 rotationMatrix;
    QMatrix4x4 translationMatrix;

    void loadArrays();
    void draw();

    void rotate(qreal angle_deg, QVector3D const& axis);
    void translate(QVector3D const& t);
};

Mesh buildSphere(double radius, int slices = 20, int stacks = 20);

#endif // GEOMETRY_H
