#version 330

//varying
in lowp vec4 v_color;

void main(void)
{
    gl_FragColor = v_color;
}

