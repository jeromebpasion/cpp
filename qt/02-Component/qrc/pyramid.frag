//pyramid.frag Fragment shader

#version 330

#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

//varying
varying lowp vec4 vary_color;

void main(void)
{
    gl_FragColor = vary_color;
}

