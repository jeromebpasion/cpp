#include "geometrydraw.h"

struct Vertex
{
    QVector3D position;
    QVector2D textureCoord;
};

GeometryDraw::GeometryDraw()
{
    //Qt OpenGL init in QOpenGLFunctions
    initializeOpenGLFunctions();

    //vbos
    pyramid_buffer.create();
   // pyramid_index.create();
    pyramid_colors.create();

    initGeometry();
}

GeometryDraw::~GeometryDraw()
{
    pyramid_buffer.destroy();
    //pyramid_index.destroy();
    pyramid_colors.destroy();
}

void GeometryDraw::initGeometry(){

   // initPyramid();
}

void GeometryDraw::initPyramid(){


    const QVector3D vertices[] = {  //rectangle base
    QVector3D(1.0f, 1.0f, 0.0f),    QVector3D(1.0f, -1.0f, 0.0f),   QVector3D(-1.0f, -1.0f, 0.0f),  //2 1 0
    QVector3D(-1.0f, 1.0f, 0.0f),   QVector3D(1.0f, 1.0f, 0.0f),    QVector3D(-1.0f, -1.0f, 0.0f),  //3 2 0
    QVector3D(-1.0f, -1.0f, 0.0f),  QVector3D(1.0f, -1.0f, 0.0f),   QVector3D(0.0f, 0.0f, 2.0f),    //0 1 4
    QVector3D(1.0f, -1.0f, 0.0f),   QVector3D(1.0f, 1.0f, 0.0f),    QVector3D(0.0f, 0.0f, 2.0f),    //1 2 4
    QVector3D(1.0f, 1.0f, 0.0f),    QVector3D(-1.0f, 1.0f, 0.0f),   QVector3D(0.0f, 0.0f, 2.0f),    //2 3 4
    QVector3D(-1.0f, 1.0f, 0.0f),   QVector3D(-1.0f, -1.0f, 0.0f),  QVector3D(0.0f, 0.0f, 2.0f)     //3 0 4
    };
//    pyramid_buffer.bind();
//    pyramid_buffer.allocate(vertices, 18 * sizeof(QVector3D));


    const GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
 //   pyramid_colors.bind();
//    pyramid_colors.allocate(colors, 9 * sizeof(GLfloat));
}


void GeometryDraw::drawPyramid(QOpenGLShaderProgram * program){
    program->bind();
//    pyramid_buffer.bind();
//    pyramid_colors.bind();


    //vertex attribute in the vertex shader (check name in vertex shader)
    int vertexAttribute = program->attributeLocation("a_vertexPos");
    if (vertexAttribute == -1){
        qDebug() << "a_vertexPos location failed";
    }
    //color attribute in the vertex shader (check name in vertex shader)
    int colorAttribute = program->attributeLocation("a_vertexColor");
    if (colorAttribute == -1){
        qDebug() << "a_vertexColor location failed";
    }

    static const GLfloat vertices[] = {

        //r
        0.0f,  2.0f, 0.0f,
        -1.0f, -1.0f, 1.0f,
         1.0f, -1.0f, 1.0f,
        //g
        0.0f,  2.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,
       -1.0f, -1.0f, 1.0f,
        //b
         0.0f,  2.0f, 0.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        //y
        0.0f,  2.0f, 0.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        //c
       -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        //m
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,

    };

    static const GLfloat colors[] = {

        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f,

        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f
    };

    //move to VAO in phase 3 (render system)
//    pyramid_colors.create();
//    pyramid_colors.bind();
//    pyramid_colors.allocate(colors, 54 * sizeof(GLfloat));

//    pyramid_buffer.create();
//    pyramid_buffer.bind();
//    pyramid_buffer.allocate(vertices, 54 * sizeof(GLfloat));

//    program->enableAttributeArray(vertexAttribute);
//    program->setAttributeBuffer(vertexAttribute, GL_FLOAT, 0, 3, 0);

//    program->enableAttributeArray(colorAttribute);
//    program->setAttributeBuffer(colorAttribute, GL_FLOAT, 0, 3, 0);

//    glDrawElements(GL_TRIANGLES, 15, GL_FLOAT, nullptr);

//    program->disableAttributeArray(colorAttribute);
//    program->disableAttributeArray(vertexAttribute);



    glEnableVertexAttribArray(vertexAttribute);
    glEnableVertexAttribArray(colorAttribute);
    glVertexAttribPointer(vertexAttribute, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 0, colors);
    glDrawArrays(GL_TRIANGLES, 0, 18);
    glDisableVertexAttribArray(colorAttribute);
    glDisableVertexAttribArray(vertexAttribute);



}

//todo: move all the drawing into here
void GeometryDraw::drawEntities(QOpenGLShaderProgram * program, const EntityManager * e_manager){

    QList<Entity*> entities = e_manager->drawables();
    //assume cube data in vbo already

}
