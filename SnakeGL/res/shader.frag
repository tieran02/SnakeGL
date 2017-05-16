#version 330 core

in vec3 FragPos;
in vec2 TexCoords;

out vec4 color;

uniform vec4 matColor;
uniform sampler2D ourTexture;


void main()
{
        vec4 texColor = texture(ourTexture, TexCoords);
    if(texColor.a < 0.1)
        discard;
    color = texColor;
}