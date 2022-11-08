#version 330 core

in vec3 vf_color;

out vec4 fo_color;

void main() {
  fo_color = vec4(vf_color, 1.0f);
}
