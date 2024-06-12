#include "windowgl.h"


WindowGL::WindowGL(){

//    cube_program = new QOpenGLShaderProgram();
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

    //test removing of entity
    e_manager->removeEntity(22);
    e_manager->removeEntity(33);

}
WindowGL::~WindowGL(){

    makeCurrent();
    delete geometries;
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

void WindowGL::initShaders(){

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
    rollAngle += 0.6;
}

void WindowGL::wheelEvent(QWheelEvent *event){
    if(event->angleDelta().y() > 0)
            zoom += 10;
    else if(event->angleDelta().y() < 0)
            zoom -= 10;

}

void WindowGL::keyPressEvent(QKeyEvent *event) {
    if(event->key() == Qt::Key_W)
    {
        camY -= camStep;
    }
    if(event->key() == Qt::Key_S)
    {
        camY += camStep;
    }
    if(event->key() == Qt::Key_A)
    {
        camX += camStep;
    }
    if(event->key() == Qt::Key_D)
    {
        camX -= camStep;
    }
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
    //glEnable(GL_CULL_FACE);
    glDisable(GL_CULL_FACE);

    //Model-View
    QMatrix4x4 mat4_modelview;
    mat4_modelview.translate(camX, camY, zoom);
    mat4_modelview.rotate(quat_rotation);
    mvp_stack.push(mat4_modelview);
    int count = 0;
    for(auto i :e_manager->drawables()){

        switch(i->shape()){

            case Entity::SPHERE:

            //todo: use cube for now;
            //break;

            case Entity::CUBE:
            break;

            case Entity::PYRAMID:
            mat4_modelview.translate(i->position());

            mat4_modelview.rotate(QQuaternion::fromEulerAngles(0,rollAngle,rollAngle));
            mat4_modelview.rotate(i->rotation());

            pyramid_program->setUniformValue("mat_mvp", mat4_projection * mat4_modelview);
            geometries->drawPyramid(pyramid_program);
            break;
        }

        count++;
        mat4_modelview = mvp_stack.top();
    }
    mat4_modelview = mvp_stack.pop();
}
