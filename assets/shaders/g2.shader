#version 330
layout (lines) in;
layout (triangle_strip, max_vertices = 4) out;

void set_position(vec4 position, float x, float y) {
    gl_Position = position + vec4(x, y, vec2(0.0));
    EmitVertex();
}

void draw_axes(vec4 position1, vec4 position2) {
    float THICKNESS = 0.02;
    set_position(position1, THICKNESS, THICKNESS);
    set_position(position1, -THICKNESS, -THICKNESS);
    set_position(position2, THICKNESS, THICKNESS);
    set_position(position2, -THICKNESS, -THICKNESS);
    EndPrimitive();
}

void main() {
    draw_axes(gl_in[0].gl_Position, gl_in[1].gl_Position);
}