#include "geometry.h"

#include <cmath>

void Mesh::loadArrays()
{
    glVertexPointer(3, GL_FLOAT, 0, vertices.constData());
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords.constData());
}

static void mulMatrix(QMatrix4x4 const& mat)
{
    double static_mat[16];
    qreal const* mat_data = mat.constData();
    for (int i = 0; i < 16; i++)
    {
        static_mat[i] = mat_data[i];
    }

    glMultMatrixd(static_mat);
}

void Mesh::draw()
{
    glPushMatrix();
      mulMatrix(translationMatrix);
      mulMatrix(rotationMatrix);

      glEnableClientState(GL_VERTEX_ARRAY);
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glDrawElements(GL_TRIANGLES, 3 * triangles.count(),
                       GL_UNSIGNED_SHORT, triangles.constData());
      glDisableClientState(GL_VERTEX_ARRAY);
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glPopMatrix();
}

void Mesh::rotate(qreal angle_deg, QVector3D const& axis)
{
    rotationMatrix.setToIdentity();
    rotationMatrix.rotate(angle_deg, axis);
}

void Mesh::translate(QVector3D const& t)
{
    translationMatrix.setToIdentity();
    translationMatrix.translate(t);
}

static void triangulate_strip(QVector<Triangle> & triangles,
                              int stack, int steps)
{
    for (int i = 0; i < steps; i++) {
        triangles.append(Triangle(stack * (steps + 1) + i,
                                  stack * (steps + 1) + i + 1,
                                  (stack + 1) * (steps + 1) + i));
        triangles.append(Triangle((stack + 1) * (steps + 1) + i,
                                  stack * (steps + 1) + i + 1,
                                  (stack + 1) * (steps + 1) + i + 1));
    }
}

Mesh buildSphere(double radius, int slices, int stacks)
{
    QVector<float> xCircle, yCircle, norm_phi;

    for (int i = 0; i <= slices; i++) {
        float phi = i / (float) slices;
        norm_phi.append(phi);
        xCircle.append(cos(2.0 * M_PI * phi));
        yCircle.append(sin(2.0 * M_PI * phi));
    }

    QVector<float> zSphere, rSphere, norm_theta;

    for (int i = 0; i <= stacks; i++) {
        float theta = i / (float) stacks;
        norm_theta.append(theta);
        zSphere.append(-cos(M_PI * theta));
        rSphere.append(sin(M_PI * theta));
    }

    Mesh mesh;

    for (int i = 0; i <= stacks; i++) {
        for (int j = 0; j <= slices; j++) {
            mesh.vertices.append(QVector3D(radius * rSphere[i] * xCircle[j],
                                           radius * zSphere[i],
                                           radius * rSphere[i] * yCircle[j]));
            mesh.texCoords.append(QVector2D(norm_phi[j], norm_theta[i]));
        }
    }

    for (int i = 0; i <= stacks; i++) {
        triangulate_strip(mesh.triangles, i, slices);
    }

    return mesh;
}
