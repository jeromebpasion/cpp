#include "src/windowgl.h"
#include <QGuiApplication>
#include <QtDebug>
#include <QtMath>
#include <QMatrix4x4>

#include <QScreen>
#include <QOpenGLShaderProgram>
#include<QSurfaceFormat>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    QSurfaceFormat surfaceFormat;
    surfaceFormat.setDepthBufferSize(24);

    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        surfaceFormat.setVersion(3,3);
        surfaceFormat.setProfile(QSurfaceFormat::CoreProfile);
    }
    else {
        surfaceFormat.setVersion(3,0);
    }
    qDebug() << "OpenGL Format:" << surfaceFormat.majorVersion() <<"." << surfaceFormat.minorVersion();
    QSurfaceFormat::setDefaultFormat(surfaceFormat);

    WindowGL windowGL;
    windowGL.showMaximized();

    return a.exec();
}
