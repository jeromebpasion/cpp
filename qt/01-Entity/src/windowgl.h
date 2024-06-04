#ifndef WINDOWGL_H
#define WINDOWGL_H

#include <QOpenGLWindow>

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>
#include <QBasicTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QMatrix4x4>
#include <QStack>
#include <QWheelEvent>

#include "geometrydraw.h"
#include "physics.h"
#include "entity.h"

using MVP = QStack<QMatrix4x4>;

class GeometryDraw;

class WindowGL : public QOpenGLWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
   // using QOpenGLWidget::QOpenGLWidget;
    WindowGL();
    ~WindowGL();

protected:

    //Qt's GL setup
    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

    //Application setup
    void initShaders();
    void initTextures();

    //controls
    void mousePressEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;
    void timerEvent(QTimerEvent *event) override;
    void wheelEvent(QWheelEvent* event) override;

private:

    //GL
    QOpenGLShaderProgram shaderProgram;

    //State
    QMatrix4x4 mat4_projection;
    //QMatrix4x4 mat4_modelview;

    //Rendering and texture
    GeometryDraw *geometries = nullptr;
    QOpenGLTexture *texture = nullptr;

    //timer for auto calls, controls
    QBasicTimer timer;
    QVector3D rotationAxis;
    QQuaternion quat_rotation;
    QVector2D mousePressPosition;
    qreal angularSpeed = 0;
    qreal zNearPlane = 1.0;
    qreal zFarPlane = 3007.0;
    qreal fov = 45;
    qreal zoom = -100;


    const qreal FRICTION = 0.99;

    PhysicsManager * p_manager;
    EntityManager * e_manager;

    MVP mvp_stack;
};

#endif // WINDOWGL_H
