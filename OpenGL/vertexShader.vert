#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectionMat;

out vec3 fragPos;
out vec3 fragNormal;

void main() {
    gl_Position = projectionMat * viewMat * modelMat * vec4(aPos, 1.0);
    fragPos = vec3(modelMat * vec4(aPos, 1.0));
    fragNormal = mat3(transpose(inverse(modelMat))) * aNormal;
}
