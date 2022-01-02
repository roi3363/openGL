#version 330
layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

uniform float time;
out float fOpacity;

void set_position(vec4 position, vec4 line_normal) {
  gl_Position = position + line_normal;
  EmitVertex();

  gl_Position = position - line_normal;
  EmitVertex();
}

void draw_line(vec4 position1, vec4 position2) {
  fOpacity = step(position2.x, 2 * fract(time) - 1.0);
  fOpacity = step(2 * fract(time - (position2.x - position1.x)) - 1.0, position2.x) * fOpacity;

  vec4 line_direction = normalize(position2 - position1);
  vec4 line_normal = vec4(-line_direction.y, line_direction.x, line_direction.zw);
  float THICKNESS = 0.005;

  vec4 scaled_line_direction = 0.5 * line_direction;
  vec4 scaled_normal = THICKNESS * line_normal;
  set_position(position1 - scaled_line_direction, scaled_normal);
  set_position(position2 + scaled_line_direction, scaled_normal);

  EndPrimitive();
}

void main() {
  draw_line(gl_in[0].gl_Position, gl_in[1].gl_Position);
}