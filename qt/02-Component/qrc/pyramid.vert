//pyramid.vert Vertex Shader

#version 330
#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

//uniform set to program
uniform mat4 mat_mvp;

//attribute in
in vec4 a_vertexPos;
in vec4 a_vertexColor;

//varying to fragment shader
varying vec4 vary_color;

void main(void)
{
    vary_color = a_vertexColor;
    gl_Position = mat_mvp * a_vertexPos;
}
