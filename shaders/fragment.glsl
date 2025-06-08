#version 330 core

out vec4 FragColor;

uniform float ambientStrength;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
    FragColor = vec4(ambientStrength * lightColor * objectColor, 1.0f);
}
