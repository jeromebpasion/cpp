#include "windowgl.h"


WindowGL::WindowGL(){
    p_manager = PhysicsManager::getSingleton();
    e_manager = EntityManager::getSingleton();

    int ent = e_manager->createEntity(Entity::CUBE);
    int ent2 =e_manager->createEntity(Entity::TRIANGLE);

    int shapeInt;
    int max = EntityManager::MAX_ENTITIES;
    for (auto i = 0; i < EntityManager::MAX_ENTITIES; ++i){


        shapeInt = QRandomGenerator::system()->bounded(0, 3);
        switch (shapeInt) {
            case 0:
                ent = e_manager->createEntity(Entity::CUBE);
            case 1:
                ent =e_manager->createEntity(Entity::SPHERE);
            case 2:
                ent =e_manager->createEntity(Entity::TRIANGLE);
        }
    }
    e_manager->removeEntity(22);
    e_manager->removeEntity(33);

}
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

    //re-bind vertex and fragment shader
    texture->bind();

    shaderProgram.bind();

    //Model-View
    QMatrix4x4 mat4_modelview;
    mat4_modelview.translate(0.0, 0.0, zoom);
    mat4_modelview.rotate(quat_rotation);

    mvp_stack.push(mat4_modelview);
    int count = 0;
    for(auto i :e_manager->drawables()){

        mat4_modelview.rotate(i->rotation());

        mat4_modelview.translate(i->position());

        //mat4_modelview.scale(0.3, 0.3, 0.3);
        shaderProgram.setUniformValue("mat_mvp", mat4_projection * mat4_modelview);
        switch(i->shape()){
            case Entity::CUBE:
                geometries->drawCube(&shaderProgram);

            case Entity::SPHERE:
                geometries->drawCube(&shaderProgram);

            case Entity::TRIANGLE:
                geometries->drawCube(&shaderProgram);
        }
        count++;
        //geometries->drawCube(&shaderProgram);
    }
    mat4_modelview = mvp_stack.pop();

   // qDebug()<< "Drawing " << count;

//    shaderProgram.setUniformValue("mat_mvp", mat4_projection * mat4_modelview);

    //texture at unit 0
    shaderProgram.setUniformValue("u_texture", 0);


    //draw
    geometries->drawCube(&shaderProgram);
    geometries->drawEntities(&shaderProgram, e_manager);
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

void WindowGL::wheelEvent(QWheelEvent *event){
    if(event->angleDelta().y() > 0)
            zoom += 10;
    else if(event->angleDelta().y() < 0)
            zoom -= 10;

}
