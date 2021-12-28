#version 330
layout (location = 0) in vec2 aPos;

out VS_OUT {
    vec2 pos;
} vs_out;

void main() {
    vs_out.pos = aPos;
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
}