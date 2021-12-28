#version 330
layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

void set_position(vec4 position, vec4 line_normal, float thickness){
    gl_Position = position + thickness * line_normal;
    EmitVertex();

    gl_Position = position - thickness * line_normal;
    EmitVertex();
}

void draw_line(vec4 position1, vec4 position2) {
  vec4 line_direction = normalize(position2 - position1);
  vec4 line_normal = vec4(-line_direction.y, line_direction.x, line_direction.zw);
  float THICKNESS = 0.02;
  
  set_position(position1, line_normal, THICKNESS);
  set_position(position2, line_normal, THICKNESS);
  EndPrimitive();
}

void main() {
    draw_line(gl_in[0].gl_Position, gl_in[1].gl_Position);
}
