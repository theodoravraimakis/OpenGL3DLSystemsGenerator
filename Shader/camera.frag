#version 410 core

in vec4 fragColor;
in vec2 fragTexCoord;
in vec3 fragNormal;
in vec3 fragPos;

out vec4 outColor;

uniform sampler2D textureSampler;
uniform bool useTexture;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float ambientStrength;
uniform float specularStrength;
uniform float shininess;

void main()
{
    vec3 color;
    if (useTexture) {
        color = texture(textureSampler, fragTexCoord).rgb;
    }
    else {
        color = fragColor.rgb;
    }

    vec3 ambient = ambientStrength * lightColor;

    vec3 lightDir = normalize(lightPos - fragPos);
    float diffuseIntensity = max(dot(fragNormal, lightDir), 0.0);
    vec3 diffuse = diffuseIntensity * lightColor;

    vec3 viewDir = normalize(-fragPos);
    vec3 reflectDir = reflect(-lightDir, fragNormal);
    float specularIntensity = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * specularIntensity * lightColor;

    vec3 result = (ambient + diffuse + specular) * color;
    outColor = vec4(result, 1.0);
}