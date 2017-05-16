#version 330 core
layout (location = 0) in vec3 position;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    //gl_Position = vec4(position, 1.0f);
}