#version 330 core

out vec4 FragColor;

void main() {
    vec3 color = vec3(0.33f, 0.46f, 0.36f);

    FragColor = vec4(color, 1.0f);
}