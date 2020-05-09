#version 150

in vec4 vPosition;
in vec4 vColor;
flat out vec4 color;
uniform mat4 Projection;

void main()
{
    gl_Position = Projection * vPosition;
    color = vColor;
}