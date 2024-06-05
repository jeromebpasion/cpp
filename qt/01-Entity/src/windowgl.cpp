#include "windowgl.h"


WindowGL::WindowGL(){

    cube_program = new QOpenGLShaderProgram();
    pyramid_program = new QOpenGLShaderProgram();

    p_manager = PhysicsManager::getSingleton();
    e_manager = EntityManager::getSingleton();


    int shapeInt;
    int max = EntityManager::MAX_ENTITIES;
    for (auto i = 0; i < EntityManager::MAX_ENTITIES; ++i){


        shapeInt = QRandomGenerator::system()->bounded(0, 3);
        switch (shapeInt) {
            case 0:
                e_manager->createEntity(Entity::CUBE);
            case 1:
                e_manager->createEntity(Entity::SPHERE);
            case 2:
                e_manager->createEntity(Entity::PYRAMID);
        }
    }
    e_manager->removeEntity(22);
    e_manager->removeEntity(33);

}
WindowGL::~WindowGL(){

    makeCurrent();
    delete geometries;
    delete cube_texture;
    delete cube_program;
    delete pyramid_program;
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

    //set new projection matrix
    mat4_projection.setToIdentity();
    mat4_projection.perspective(fov, aspectRatio, zNearPlane, zFarPlane);

}

//re-set GL settings, buffers, state, render call
void WindowGL::paintGL(){

    //reset GL context
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);


    //Model-View
    QMatrix4x4 mat4_modelview;
    mat4_modelview.translate(0.0, 0.0, zoom);
    mat4_modelview.rotate(quat_rotation);

    mvp_stack.push(mat4_modelview);
    int count = 0;
    for(auto i :e_manager->drawables()){

        switch(i->shape()){
            case Entity::CUBE:
            mat4_modelview.translate(i->position());
            mat4_modelview.rotate(i->rotation());
            cube_program->setUniformValue("mat_mvp", mat4_projection * mat4_modelview);
            cube_texture->bind();
            cube_program->bind();
            geometries->drawCube(cube_program);

            case Entity::SPHERE:
            mat4_modelview.translate(i->position());
            mat4_modelview.rotate(i->rotation());
            cube_program->setUniformValue("mat_mvp", mat4_projection * mat4_modelview);
            //geometries->drawCube(cube_program);

            case Entity::PYRAMID:
            mat4_modelview.translate(i->position());
            mat4_modelview.rotate(i->rotation());
            cube_program->setUniformValue("mat_mvp", mat4_projection * mat4_modelview);
            pyramid_program->bind();
            geometries->drawPyramid(pyramid_program);
        }

        count++;
    }
    mat4_modelview = mvp_stack.pop();

    //draw
    geometries->drawEntities(cube_program, e_manager);
}

void WindowGL::initShaders(){

    //initialize Cube shaders first. with texture
    cube_program->create();
    try {
        cube_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/cube.frag");
        cube_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/cube.vert");
        cube_program->link();
        cube_program->bind();

        QString cubelog = cube_program->log();
        if (!cubelog.isEmpty())
            qDebug() << cubelog;
    }  catch (...) {
        qDebug() << "Exception Cube Shader: \n";
        qDebug() << cube_program->log();
    }

    //initialize Pyramid. With basic colors
    pyramid_program->create();
    try {
        pyramid_program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/pyramid.frag");
        pyramid_program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/pyramid.vert");
        pyramid_program->link();
        pyramid_program->bind();

        QString pyramidlog = pyramid_program->log();
        if (!pyramidlog.isEmpty())
            qDebug() << pyramidlog;
    }  catch (...) {
        qDebug() << "Exception Pyramid Shader: \n";
        qDebug() << pyramid_program->log();
    }

}

void WindowGL::initTextures(){

    cube_texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    cube_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    cube_texture->setMagnificationFilter(QOpenGLTexture::Linear);

    cube_texture->setWrapMode(QOpenGLTexture::Repeat);
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

void WindowGL::wheelEvent(QWheelEvent *event){
    if(event->angleDelta().y() > 0)
            zoom += 10;
    else if(event->angleDelta().y() < 0)
            zoom -= 10;

}
