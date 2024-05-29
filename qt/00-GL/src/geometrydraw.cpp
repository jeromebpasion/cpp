#include "geometrydraw.h"
#include <QVector3D>
#include <QVector2D>

struct Vertex
{
    QVector3D position;
    QVector2D textureCoord;
};


GeometryDraw::GeometryDraw()
    : indexBuffer(QOpenGLBuffer::IndexBuffer)
{
    //Qt OpenGL init in QOpenGLFunctions
    initializeOpenGLFunctions();

    //vbos
    arrayBuffer.create();
    indexBuffer.create();

    initGeometry();
}

GeometryDraw::~GeometryDraw()
{

}

void GeometryDraw::initGeometry(){


}

void GeometryDraw::initCube(){

    Vertex vertices[] = {
        // {position, textureCoord}                                   index

        //face 0
        {QVector3D(-1.0f, -1.0f, 1.0f), QVector2D(0.0f, 0.0f)}, //v0    0
        {QVector3D(-1.0f, -1.0f, 1.0f), QVector2D(0.0f, 0.0f)}, //v1    1
        {QVector3D(-1.0f, -1.0f, 1.0f), QVector2D(0.0f, 0.0f)}, //v2    2
        {QVector3D(-1.0f, -1.0f, 1.0f), QVector2D(0.0f, 0.0f)}, //v3    3

        //face 1
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)}, //v0   4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.0f, 0.0f)}, //v1   5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.0f)}, //v2   6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.0f, 0.0f)}, //v3   7

        //face 2
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.0f, 0.0f)}, //v0   8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.0f, 0.0f)}, //v1   9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.0f, 0.0f)}, //v2   10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.0f, 0.0f)}, //v3   11

        //face 3
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.0f, 0.0f)}, //v0   12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)}, //v1   13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.0f, 0.0f)}, //v2   14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.0f)}, //v3   15

        //face 4
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.0f, 0.0f)}, //v0   16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.0f, 0.0f)}, //v1   17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)}, //v2   18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)}, //v3   19

        //face 5
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.0f)}, //v0   20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.0f)}, //v1   21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.0f, 0.0f)}, //v2   22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.0f, 0.0f)}  //v3   23
    };

    GLushort vertexIndices[] = {
        0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
        4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
        8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
       12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
       16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
       20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)

    };

    arrayBuffer.bind();
    arrayBuffer.allocate(vertices, 24 * sizeof(Vertex));

    indexBuffer.bind();
    indexBuffer.allocate(vertexIndices, 34 * sizeof(GLushort));

}

void GeometryDraw::initTriangle(){


}

void GeometryDraw::drawCube(QOpenGLShaderProgram * program) {
    //assume cube data in vbo already

    arrayBuffer.bind();
    indexBuffer.bind();

    //buffer offset. start at beginning of buffer
    quintptr vertexOffset = 0, textureOffset = sizeof(QVector3D);
    int vertexNum = 3, textNum = 2, triangles = 34;

    //vertex attribute in the shader (check name in shader)
    int vertexAttribute = program->attributeLocation("a_Vertex");
    program->enableAttributeArray(vertexAttribute);
    program->setAttributeBuffer(vertexAttribute, GL_FLOAT, vertexOffset, vertexNum, sizeof(Vertex));

    glDrawElements(GL_TRIANGLE_STRIP, triangles, GL_UNSIGNED_SHORT, nullptr);

}
