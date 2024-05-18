#ifndef WINDOWGL_H
#define WINDOWGL_H

#include <QOpenGLWindow>
#include <QOpenGLFunctions>


class WindowGL : public QOpenGLWindow, protected QOpenGLFunctions
{
public:
    WindowGL();
};

#endif // WINDOWGL_H
