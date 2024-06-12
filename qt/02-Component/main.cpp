#include "src/windowgl.h"

#include <QtDebug>
#include <QGuiApplication>
#include <QSurfaceFormat>
#include <QOpenGLContext>

int main(int argc, char *argv[])
{

    QSurfaceFormat surfaceFormat;
    surfaceFormat.setDepthBufferSize(24);
    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
         surfaceFormat.setProfile(QSurfaceFormat::CoreProfile);
        //surfaceFormat.setVersion(3,3);// doesnt work. only 2.0. need new opengl context
        std::cout << glGetError() << std::endl;

    }
    else {
        surfaceFormat.setVersion(3,0);
    }
    QSurfaceFormat::setDefaultFormat(surfaceFormat);
    qDebug() << "OpenGL Format:" << surfaceFormat.majorVersion() <<"." << surfaceFormat.minorVersion();

//    QSurfaceFormat fmt;
//    fmt.setDepthBufferSize(24);

//    // Request OpenGL 3.3 core or OpenGL ES 3.0.
//    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
//        qDebug("Requesting 3.3 core context");
//        fmt.setVersion(3, 3);
//        fmt.setProfile(QSurfaceFormat::CoreProfile);
//    } else {
//        qDebug("Requesting 3.0 context");
//        fmt.setVersion(3, 0);
//    }

//   qDebug() << "OpenGL Format:" << fmt.majorVersion() <<"." << fmt.minorVersion();

//    QSurfaceFormat::setDefaultFormat(fmt);
//    std::cout << glGetError() << std::endl; // returns 1280 (invalid enum)

    QGuiApplication a(argc, argv);
    WindowGL windowGL;
    windowGL.resize(500,400);
    windowGL.show();

    return a.exec();

}
