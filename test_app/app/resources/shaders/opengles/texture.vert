#version 300 es

precision highp float;

uniform mat4 u_model_view_projection;

layout (location = 0) in vec3 iv_position;
layout (location = 1) in vec3 iv_color;
layout (location = 2) in vec2 iv_tex_coord;

out vec3 vf_color;
out vec2 vf_tex_coord;

void main() {
  gl_Position = u_model_view_projection * vec4(iv_position, 1.0f);
  vf_color = iv_color;
  vf_tex_coord = iv_tex_coord;
}
