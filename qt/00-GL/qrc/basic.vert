attribute vec4 a_Vertex;
attribute vec4 a_MultiTexCoord0;
uniform mat4 mat_ModelViewProjectionMatrix;
varying vec4 vary_TexCoord0;

void main(void)
{
    gl_Position = mat_ModelViewProjectionMatrix * a_Vertex;
    vary_TexCoord0 = a_MultiTexCoord0;
}
