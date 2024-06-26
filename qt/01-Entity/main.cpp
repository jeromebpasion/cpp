#include "src/windowgl.h"

#include <QGuiApplication>
#include <QtDebug>
#include <QtMath>
#include <QMatrix4x4>
#include <QScreen>
#include <QOpenGLShaderProgram>
#include <QSurfaceFormat>
#include <iostream>


int main(int argc, char *argv[])
{

    QSurfaceFormat surfaceFormat;
    surfaceFormat.setDepthBufferSize(24);

    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        //surfaceFormat.setVersion(3,2);// doesnt work on machine. only 2.0. need new opengl context
        surfaceFormat.setProfile(QSurfaceFormat::CoreProfile);

        std::cout << glGetError() << std::endl;

    }
    else {
        surfaceFormat.setVersion(3,0);
    }
   qDebug() << "OpenGL Format:" << surfaceFormat.majorVersion() <<"." << surfaceFormat.minorVersion();


    QSurfaceFormat::setDefaultFormat(surfaceFormat);
    std::cout << glGetError() << std::endl; // returns 1280 (invalid enum)

    QGuiApplication a(argc, argv);
    WindowGL windowGL;
    windowGL.resize(500,400);
    windowGL.show();

    return a.exec();

}
