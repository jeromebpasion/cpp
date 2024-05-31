#include "src/windowgl.h"
#include <QGuiApplication>
#include <QtDebug>
#include <QtMath>
#include <QMatrix4x4>

#include <QScreen>
#include <QOpenGLShaderProgram>
#include <QSurfaceFormat>


int main(int argc, char *argv[])
{

    QSurfaceFormat surfaceFormat;
    surfaceFormat.setDepthBufferSize(24);

    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        surfaceFormat.setVersion(4,2);// 4.6 doesnt work on machine. only 2.0. need new opengl context
        surfaceFormat.setProfile(QSurfaceFormat::CoreProfile);
    }
    else {
        surfaceFormat.setVersion(3,0);
    }
   qDebug() << "OpenGL Format:" << surfaceFormat.majorVersion() <<"." << surfaceFormat.minorVersion();


    //QSurfaceFormat::setDefaultFormat(surfaceFormat);

    QGuiApplication a(argc, argv);
    WindowGL windowGL;
    windowGL.resize(500,400);
    windowGL.show();

    return a.exec();

}
