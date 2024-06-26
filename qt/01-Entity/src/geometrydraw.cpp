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
    //pyramid_index = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    pyramid_index.create();
    pyramid_colors.create();

    cube_buffer.create();
    cube_index = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    cube_index.create();


    qDebug() << cube_index.type() << pyramid_index.type();

    initGeometry();
}

GeometryDraw::~GeometryDraw()
{
    cube_buffer.destroy();
    cube_index.destroy();

    pyramid_buffer.destroy();
    pyramid_index.destroy();
    pyramid_colors.destroy();
}

void GeometryDraw::initGeometry(){

    initCube();
    initPyramid();
}

//initialize cube geometry and load into vbo
void GeometryDraw::initCube(){

    GLushort vertexIndices[] = { // 34 indices
        0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
        4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
        8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
       12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
       16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
       20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

  Vertex vertices[]  = {    //24 vertices
            // Vertex data for face 0
            {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
            {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
            {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
            {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3

            // Vertex data for face 1
            {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
            {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
            {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
            {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7

            // Vertex data for face 2
            {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
            {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
            {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
            {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11

            // Vertex data for face 3
            {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
            {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
            {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
            {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15

            // Vertex data for face 4
            {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
            {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
            {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
            {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19

            // Vertex data for face 5
            {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
            {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
            {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
            {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
        };


      cube_buffer.bind();
      cube_buffer.allocate(vertices, 24 * sizeof(Vertex));

      cube_index.bind();
      cube_index.allocate(vertexIndices, 34 * sizeof(GLushort));
}

void GeometryDraw::initPyramid(){

//    const QVector3D verticesIndexed[] = {  //rectangle base
//    QVector3D(-1.0f, -1.0f, 0.0f),  //base 0
//    QVector3D(1.0f, -1.0f, 0.0f),   //base 1
//    QVector3D(1.0f, 1.0f, 0.0f),    //base 2
//    QVector3D(-1.0f, 1.0f, 0.0f),   //base 3
//    QVector3D(0.0f, 0.0f, 2.0f)     //top  4
//    };
//    pyramid_buffer.bind();
//    pyramid_buffer.allocate(verticesIndexed, 5 * sizeof(QVector3D));

//    const GLushort vertexIndices[] = {  //ccw order
//        2, 1, 0,    3, 2, 0,                            //base triangle 1 and 2
//        0, 1, 4,    1, 2, 4,    2, 3, 4,    3, 0, 4     //side triangles
//    };
//    pyramid_index.bind();
//    pyramid_index.allocate(vertexIndices, 18 * sizeof(GLushort));


    const QVector3D vertices[] = {  //rectangle base
    QVector3D(1.0f, 1.0f, 0.0f),    QVector3D(1.0f, -1.0f, 0.0f),   QVector3D(-1.0f, -1.0f, 0.0f),  //2 1 0
    QVector3D(-1.0f, 1.0f, 0.0f),   QVector3D(1.0f, 1.0f, 0.0f),    QVector3D(-1.0f, -1.0f, 0.0f),  //3 2 0
    QVector3D(-1.0f, -1.0f, 0.0f),  QVector3D(1.0f, -1.0f, 0.0f),   QVector3D(0.0f, 0.0f, 2.0f),    //0 1 4
    QVector3D(1.0f, -1.0f, 0.0f),   QVector3D(1.0f, 1.0f, 0.0f),    QVector3D(0.0f, 0.0f, 2.0f),    //1 2 4
    QVector3D(1.0f, 1.0f, 0.0f),    QVector3D(-1.0f, 1.0f, 0.0f),   QVector3D(0.0f, 0.0f, 2.0f),    //2 3 4
    QVector3D(-1.0f, 1.0f, 0.0f),   QVector3D(-1.0f, -1.0f, 0.0f),  QVector3D(0.0f, 0.0f, 2.0f)     //3 0 4
    };
    pyramid_buffer.bind();
    pyramid_buffer.allocate(vertices, 18 * sizeof(QVector3D));


    const GLfloat colors[] = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    };
    pyramid_colors.bind();
    pyramid_colors.allocate(colors, 9 * sizeof(GLfloat));
}

//draw the cube. bind buffers, link attributes/varying, call glDrawElements
void GeometryDraw::drawCube(QOpenGLShaderProgram * program) {

    program->bind();
    cube_buffer.bind();
    cube_index.bind();

    //buffer offset. start at beginning of buffer
    quintptr vertexOffset = 0;
    int numberVertices = 3;

    //vertex attribute in the shader (check name in shader)
    int vertexAttribute = program->attributeLocation("a_vertexPos");
    if (vertexAttribute == -1){
        qDebug() << "a_vertexPos location failed";
    }
    program->enableAttributeArray(vertexAttribute);
    program->setAttributeBuffer(vertexAttribute, GL_FLOAT, vertexOffset, numberVertices, sizeof(Vertex));

    //set up texture location and enable
    quintptr textureOffset = sizeof(QVector3D);
    int texNum = 2;
    int textureAttribute = program->attributeLocation("a_textureCoord");
    program->enableAttributeArray(textureAttribute);
    program->setAttributeBuffer(textureAttribute, GL_FLOAT, textureOffset, texNum, sizeof(Vertex));

    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, nullptr);

    //program->release();
}

void GeometryDraw::drawPyramid(QOpenGLShaderProgram * program){

    program->bind();
    pyramid_buffer.bind();
    pyramid_index.bind();
    pyramid_colors.bind();


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

    program->enableAttributeArray(vertexAttribute);
    program->setAttributeBuffer(vertexAttribute, GL_FLOAT, 0, 3, 0);

    program->enableAttributeArray(colorAttribute);


    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);

    //program->release();
}

//todo: move all the drawing into here
void GeometryDraw::drawEntities(QOpenGLShaderProgram * program, const EntityManager * e_manager){

    QList<Entity*> entities = e_manager->drawables();
    //assume cube data in vbo already

}
