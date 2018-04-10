#version 330

out vec4 FragColor;
in vec4 Color;
in vec2 TexCoord;

uniform sampler2D outTexture;

void main()
{
    FragColor = Color;
    //FragColor = gl_FragCoord;
    //FragColor.a = 0.5;
    //FragColor = texture(outTexture,TexCoord);
}
