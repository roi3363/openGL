#version 330
layout (points) in;
layout (triangle_strip, max_vertices = 10) out;
//layout (points, max_vertices = 1) out;

in VS_OUT {
    vec2 pos;
} gs_in[];

out vec2 aPos;

void set_position(vec4 position, float x, float y) {
    gl_Position = position + vec4(x, y, vec2(0.0));
    EmitVertex();
}

void draw_axes(vec4 position) {
    float THICKNESS = 0.002;
    set_position(position, -1.0, -THICKNESS);
    set_position(position, 1.0, -THICKNESS);
    set_position(position, -1.0, THICKNESS);
    set_position(position, 1.0, THICKNESS);
    set_position(position, 0.0, 0.0);
    set_position(position, 0.0, 0.0);
    set_position(position, -THICKNESS, -1.0);
    set_position(position, THICKNESS, -1.0);
    set_position(position, -THICKNESS, 1.0);
    set_position(position, THICKNESS, 1.0);
    EndPrimitive();
}

void main() {
    gl_Position = gl_in[0].gl_Position;
    draw_axes(gl_in[0].gl_Position);
}