#version 330
layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

in float tStep[];

uniform float time;
out float fOpacity;

void set_position(vec4 position, vec4 line_normal, float thickness){
    gl_Position = position + thickness * line_normal;
    EmitVertex();

    gl_Position = position - thickness * line_normal;
    EmitVertex();
}

void draw_line(vec4 position1, vec4 position2) {
  vec4 line_direction = normalize(position2 - position1);
  vec4 line_normal = vec4(-line_direction.y, line_direction.x, line_direction.zw);
  float THICKNESS = 0.01;

  fOpacity = step((tStep[1] + 1.0) / 2.0, 2.0 * fract(time) - 1.0);
  
  set_position(position1 - 0.01 * line_direction, line_normal, THICKNESS);
  set_position(position2 + 0.01 * line_direction, line_normal, THICKNESS);
  EndPrimitive();
}

void main() {
    draw_line(gl_in[0].gl_Position, gl_in[1].gl_Position);
}
