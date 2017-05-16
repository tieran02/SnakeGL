#version 330 core

in vec3 FragPos;

out vec4 color;

uniform vec4 matColor;
uniform sampler2D texture_diffuse1;

void main()
{
    color = matColor;
}