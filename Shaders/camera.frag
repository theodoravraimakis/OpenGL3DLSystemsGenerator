#version 410 core

in vec4 color;
//in vec3  normal;

out vec4 fragColor;

void main()
{
   //vec3 fragNormal = normalize(normal);
   fragColor = color;
}