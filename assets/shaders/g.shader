#version 330
layout (lines) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
    vec2 pos;
} gs_in[];

out vec2 aPos;

void build_house(vec4 position)
{
    float x = 1.0;
    float y = 0.2;
    gl_Position = position + vec4(-x, -y, 0.0, 0.0);// 1:bottom-left
    EmitVertex();
    gl_Position = position + vec4(x, -y, 0.0, 0.0);// 2:bottom-right
    EmitVertex();
    gl_Position = position + vec4(-x, y, 0.0, 0.0);// 3:top-left
    EmitVertex();
//    gl_Position = position + vec4(x, y, 0.0, 0.0);// 4:top-right
//    EmitVertex();
    EndPrimitive();
}

void main() {
    gl_Position = gl_in[0].gl_Position;
    build_house(gl_Position);
    //    EmitVertex();
    //    EndPrimitive();
}