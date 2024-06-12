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
    void keyPressEvent(QKeyEvent *event) override;

private:

    //GL programs
    QOpenGLShaderProgram *cube_program = nullptr;
    QOpenGLShaderProgram * pyramid_program = nullptr;
    QOpenGLTexture * cube_texture = nullptr;

    //State
    QMatrix4x4 mat4_projection;
    MVP mvp_stack;

    //Rendering
    GeometryDraw *geometries = nullptr;

    //timer for auto calls, controls
    QBasicTimer timer;
    QVector3D rotationAxis;
    QQuaternion quat_rotation;
    QVector2D mousePressPosition;
    qreal angularSpeed = 0;
    qreal zNearPlane = 1.0;
    qreal zFarPlane = 500.0;
    qreal fov = 45;
    qreal zoom = -100;
    qreal rollAngle = 0.0;
    qreal camX = 0.0;
    qreal camY = 0.0;
    qreal camStep = 1.0;

    const qreal FRICTION = 0.98;

    PhysicsManager * p_manager;
    EntityManager * e_manager;

};

#endif // WINDOWGL_H
