#version 410 core

layout(location = 0) in vec3 aPos;
// layout(location = 1) in vec4 aColor;
layout(location = 2) in vec3 aNormal;

out vec3 fragPos;
out vec4 color;
out vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//uniform mat3 normalMatrix;

void main(){
   gl_Position = projection * view * model * vec4(aPos, 1.0f);
//    color = aColor;
   fragPos = aPos;
   normal = aNormal;
}