#version 410 core

layout(location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;
layout(location = 3) in vec4 aColor;

out vec3 fragPos;
out vec3 fragNormal;

out vec2 fragTexCoord;
out vec4 fragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
   gl_Position = projection * view * model * vec4(aPos, 1.0f);

   fragPos = vec3(model * vec4(aPos, 1.0f));
   fragNormal = normalize(mat3(transpose(inverse(model * view))) * aNormal);

   fragColor = aColor;
   fragTexCoord = aTexCoord;

}
