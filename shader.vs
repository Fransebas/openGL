#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 aTextCoord;

out vec4 Color;
out vec2 TexCoord;

uniform mat4 xRot;
uniform mat4 yRot;
uniform mat4 zRot;

void main()
{
    gl_Position = xRot * yRot * zRot * vec4(Position/0.5, 1.0);
    Color = vec4( color, 1.0);
    //Color = vec4(Position, 1.0);
    TexCoord = aTextCoord;
}
