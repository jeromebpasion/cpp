#version 330

#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D u_texture;

//varying in
in vec2 vary_textureCoord;

void main()
{
    gl_FragColor = texture2D(u_texture, vary_textureCoord);
}

