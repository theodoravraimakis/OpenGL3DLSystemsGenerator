#version 410 core

uniform vec4 color;
//in vec3  normal;

out vec4 fragColor;

void main()
{
   // ambient
   float ambientStrength = 0.1;
//    vec3 ambient = ambientStrength * lightColor;

   //vec3 fragNormal = normalize(normal);
   fragColor = color;
}