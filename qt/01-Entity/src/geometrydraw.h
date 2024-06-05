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
    void drawPyramid(QOpenGLShaderProgram * program);
    void drawEntities(QOpenGLShaderProgram * program, const EntityManager * e_manager);

private:
    void initGeometry();
    void initCube();
    void initPyramid();

    //vbo fbo
    QOpenGLBuffer cube_buffer;
    QOpenGLBuffer cube_index;
    QOpenGLBuffer pyramid_buffer;
    QOpenGLBuffer pyramid_index;
    QOpenGLBuffer pyramid_colors;
    QOpenGLBuffer buffer_sphere;
    QOpenGLBuffer index_sphere;
};

#endif // GEOMETRYDRAW_H
