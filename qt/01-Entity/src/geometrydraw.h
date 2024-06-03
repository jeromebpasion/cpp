#ifndef GEOMETRYDRAW_H
#define GEOMETRYDRAW_H

#include <QObject>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QVector3D>
#include <QVector2D>
#include <QtDebug>

#include "entity.h"

class GeometryDraw: public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GeometryDraw();
    virtual ~GeometryDraw();

    void drawGeometry(QOpenGLShaderProgram * program);
    void drawCube(QOpenGLShaderProgram * program);
    void drawTriangle(QOpenGLShaderProgram * program);
    void drawEntities(QOpenGLShaderProgram * program, const EntityManager * e_manager);

private:
    void initGeometry();
    void initCube();
    void initTriangle();

    //vbo fbo
    QOpenGLBuffer arrayBuffer;
    QOpenGLBuffer indexBuffer;
};

#endif // GEOMETRYDRAW_H
