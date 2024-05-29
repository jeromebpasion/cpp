#include "windowgl.h"

WindowGL::WindowGL()
{

}

WindowGL::~WindowGL(){

    delete geometries;
    delete texture;

}


//Qt's GL setup
void WindowGL::initializeGL(){

    initializeOpenGLFunctions();

    glClearColor(0.5, 0.5, 0.5, 1);

    initShaders();
    initTextures();

    geometries = new GeometryDraw;
}

void WindowGL::resizeGL(int width, int height){

    //Re-calculate aspect ratio, FOV, and camera-related
    qreal aspectRatio = qreal(width) / qreal(height ? height : 1);
    const qreal zNearPlane = 3.0, zFarPlane = 7.0, fov = 60;

    //set new projection matrix
    mat4_projection.setToIdentity();
    mat4_projection.perspective(fov, aspectRatio, zNearPlane, zFarPlane);
}

//re-set GL settings, buffers, state
void WindowGL::paintGL(){

    //reset GL context
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    //re-bind vertex and fragment shader
    shaderProgram.bind();

    //Model-View
    mat4_modelview.translate(0.0, 0.0, -10.0);
    mat4_modelview.rotate(quat_rotation);

    //set model-view-projection matrix in shader
    shaderProgram.setUniformValue("mat_ModelViewProjectionMatrix", mat4_projection * mat4_modelview);

    geometries->drawCube(&shaderProgram);
}

void WindowGL::initShaders(){

    try {
        shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/basic.frag");
    }  catch (...) {
        qDebug() << "Exception Fragment Shader: \n";
        qDebug() << shaderProgram.log();
    }

    try {
        shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/basic.vert");
    }  catch (...) {
        qDebug() << "Exception Vertex Shader: \n";
        qDebug() << shaderProgram.log();
    }

    try {
        shaderProgram.link();
    }  catch (...) {
        qDebug() << "Exception Linking: \n";
        qDebug() << shaderProgram.log();
    }
    try {
        shaderProgram.bind();
    }  catch (...) {
        qDebug() << "Exception Binding: \n";
        qDebug() << shaderProgram.log();
    }
}

void WindowGL::initTextures(){

}

void WindowGL::mousePressEvent(QMouseEvent * event){

}
void WindowGL::mouseReleaseEvent(QMouseEvent * event){

}
void WindowGL::timerEvent(QTimerEvent *event){

}
