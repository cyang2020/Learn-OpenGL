#version 330 core

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

in vec3 fragPos;
in vec3 fragNormal;
uniform vec3 objColor;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

out vec4 fragColor;

void main() {
    vec3 ambientColor = material.ambient * light.ambient;
    
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 diffuseColor = (material.diffuse * max(dot(normalize(fragNormal), lightDir), 0)) * light.diffuse;
    
    vec3 reflectDir = reflect(-lightDir, fragNormal);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 specularColor = (material.specular * pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess)) * light.specular;

    fragColor = vec4((ambientColor + diffuseColor + specularColor) * objColor, 1.0);
}
