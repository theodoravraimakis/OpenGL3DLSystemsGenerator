#version 410 core

in vec3  normal;
in vec3 fragPos;

uniform vec3 color;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform float ambientStrength;

out vec4 fragColor;

void main()
{
   // ambient
//    float ambientStrength = 0.5;
   vec3 ambient = ambientStrength * lightColor;
   vec3 lightDirection = normalize(lightPosition - fragPos);

   vec3 fragNormal = normalize(normal);
   float diffuseImpact = max(dot(fragNormal, lightDirection), 0.0);
   vec3 diffuse = diffuseImpact * lightColor;

   vec3 finalColor = (ambient + diffuse) * color;

   fragColor = vec4(finalColor, 1.0);
}