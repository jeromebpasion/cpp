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
    void drawPyramid(QOpenGLShaderProgram * program);
    void drawEntities(QOpenGLShaderProgram * program, const EntityManager * e_manager);

private:
    void initGeometry();
    void initPyramid();

    //vbo fbo
    QOpenGLBuffer pyramid_buffer;
    QOpenGLBuffer pyramid_colors;
};

#endif // GEOMETRYDRAW_H
