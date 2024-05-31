#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mat_mvp;

attribute vec4 a_vertexPos;
attribute vec2 a_textureCoord;

varying vec2 vary_textureCoord;

void main()
{
    vary_textureCoord = a_textureCoord;

    gl_Position = mat_mvp * a_vertexPos;
}
