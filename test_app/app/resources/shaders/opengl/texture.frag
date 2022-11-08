#version 330 core

uniform sampler2D u_color_texture;

in vec3 vf_color;
in vec2 vf_tex_coord;

out vec4 fo_color;

void main() {
  fo_color = texture(u_color_texture, vf_tex_coord);
}
