#version 330 core
in vec3 vertexColor;
in vec2 texCord;
out vec4 fragColor;
uniform sampler2D ourTex;
uniform sampler2D ourFaceTex;

void main() {
    fragColor = mix(texture(ourTex, texCord) , texture(ourFaceTex, texCord), 0.2);
}
