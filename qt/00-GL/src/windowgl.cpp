#include "windowgl.h"


WindowGL::~WindowGL(){

    makeCurrent();
    delete geometries;
    delete texture;
    doneCurrent();

}

//Qt's GL setup
void WindowGL::initializeGL(){

    initializeOpenGLFunctions();

    glClearColor(0.5, 0.6, 0.5, 1);

    initShaders();
    initTextures();

    geometries = new GeometryDraw;

    timer.start(12, this);

}

void WindowGL::resizeGL(int width, int height){

    //Re-calculate aspect ratio, FOV, and camera-related
    qreal aspectRatio = qreal(width) / qreal(height ? height : 1);
    const qreal zNearPlane = 3.0, zFarPlane = 7.0, fov = 50;

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
    texture->bind();

    shaderProgram.bind();

    //Model-View
    QMatrix4x4 mat4_modelview;
    mat4_modelview.translate(0.0, 0.0, -5.0);
    mat4_modelview.rotate(quat_rotation);

    //vertex shader
    // uniform mat4 mat_mvp;
    //attribute vec4 a_vertexPos;
    //attribute vec2 a_textureCoord;
    //Svarying vec2 vary_textureCoord;

    //frag shader
    // uniform sampler2D u_texture;
    //varying vec2 vary_textureCoord;
    //set model-view-projection matrix in shader

    shaderProgram.setUniformValue("mat_mvp", mat4_projection * mat4_modelview);

    //texture at unit 0
    shaderProgram.setUniformValue("u_texture", 0);


    //draw
    geometries->drawCube(&shaderProgram);

}

void WindowGL::initShaders(){

    shaderProgram.create();

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

    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void WindowGL::mousePressEvent(QMouseEvent * event){
    mousePressPosition = QVector2D(event->position());
}
void WindowGL::mouseReleaseEvent(QMouseEvent * event){

    QVector2D delta = QVector2D(event->position()) - mousePressPosition;
    QVector3D normal = QVector3D(delta.y(), delta.x(), 0.0).normalized();

    qreal accelerate = delta.length() / 100.0;

    rotationAxis = (rotationAxis * angularSpeed + normal*accelerate).normalized();
    angularSpeed += accelerate;

}
void WindowGL::timerEvent(QTimerEvent *event){

    //decay, friction
    angularSpeed *= FRICTION;

    //round down
    if(angularSpeed < 0.01){
        angularSpeed = 0.000;
    } else {
        quat_rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * quat_rotation;
    }

    //update widget
    update();
}
