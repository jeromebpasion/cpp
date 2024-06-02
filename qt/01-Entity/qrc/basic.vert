#version 330

#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mat_mvp;

//attribute in
in vec4 a_vertexPos;
in vec2 a_textureCoord;

//varying out
out vec2 vary_textureCoord;

void main()
{
    vary_textureCoord = a_textureCoord;

    gl_Position = mat_mvp * a_vertexPos;
}
