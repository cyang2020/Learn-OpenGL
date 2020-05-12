#version 330 core

struct Light {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
struct PointLight{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};
struct SpotLight{
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float cutoff;
    float cutoffOuter;
};
struct Material {
    sampler2D texture_diffuse;
    sampler2D texture_specular;
    float shininess;
};

in vec3 fragPos;
in vec3 fragNormal;
in vec2 textureCoord;

//uniform vec3 objColor;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform PointLight pointLight;
uniform SpotLight spotLight;
out vec4 fragColor;

vec3 calcPointLight(vec3 fragNormal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(pointLight.position - fragPos);
    float lightLength = length(pointLight.position - fragPos);
    vec3 reflectDir = reflect(-lightDir, fragNormal);
    
    float attenuation = 1.0 / (pointLight.constant + pointLight.linear * lightLength + pointLight.quadratic * (lightLength * lightLength));
    float diffuseVector = max(dot(normalize(fragNormal), lightDir), 0);
    float specularVector = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
    
    vec3 tex = texture(material.texture_diffuse, textureCoord).rgb;
    vec3 ambientColor = pointLight.ambient * tex;
    vec3 diffuseColor = pointLight.diffuse * diffuseVector * tex;
    vec3 specularColor = pointLight.specular * specularVector * tex;
    
    ambientColor *= attenuation;
    diffuseColor *= attenuation;
    specularColor *= attenuation;
    
    return (ambientColor + diffuseColor + specularColor);
}
vec3 calcDirLight(vec3 fragNormal, vec3 viewDir) {
    vec3 tex = texture(material.texture_diffuse, textureCoord).rgb;
    vec3 texSpecular = texture(material.texture_specular, textureCoord).rgb;
    
    vec3 ambientColor = tex * light.ambient;
    
    vec3 lightDir = normalize(-light.direction);
    float diffuseVector = max(dot(normalize(fragNormal), lightDir), 0);
    vec3 diffuseColor = tex * diffuseVector * light.diffuse;
    
    vec3 reflectDir = reflect(-lightDir, fragNormal);

    float specularVector = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
    vec3 specularColor = texSpecular * specularVector * light.specular;
    return (ambientColor + diffuseColor + specularColor);
}
vec3 calcSpotLight(vec3 fragNormal, vec3 viewDir){
    vec3 tex = texture(material.texture_diffuse, textureCoord).rgb;
    vec3 texSpecular = texture(material.texture_specular, textureCoord).rgb;
    vec3 lightDir = normalize(spotLight.position - fragPos);
    
    vec3 ambientColor = tex * spotLight.ambient;
    float diffuseVector = max(dot(normalize(fragNormal), lightDir), 0);
    vec3 diffuseColor = tex * diffuseVector * spotLight.diffuse;
    vec3 reflectDir = reflect(-lightDir, fragNormal);
    float specularVector = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess);
    vec3 specularColor = texSpecular * specularVector * light.specular;

    float theta = dot(lightDir, normalize(-spotLight.direction));
    float intensity = clamp((theta - spotLight.cutoffOuter) / (spotLight.cutoff - spotLight.cutoffOuter), 0.0, 1.0);
    diffuseColor *= intensity;
    specularColor *= intensity;
    
    return (ambientColor + diffuseColor + specularColor);
}

void main() {
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 result = calcDirLight(fragNormal, viewDir);
    result += calcPointLight(fragNormal, fragPos, viewDir);
    result += calcSpotLight(fragNormal, viewDir);
    fragColor = vec4(result, 1.0);
}
