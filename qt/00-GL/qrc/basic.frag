uniform sampler2D u_Texture0;
varying vec4 vary_TexCoord0;

void main(void)
{
    gl_FragColor = texture2D(u_Texture0, vary_TexCoord0.st);
}
