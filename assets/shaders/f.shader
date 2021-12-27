#version 330
out vec4 FragColor;
in vec2 aPos;

float grid(vec2 st, float res) {
    vec2 grid = fract(st*res);
    return 1.0 - (step(res,grid.x) * step(res,grid.y));
}

float axis(vec2 st, float thickness) {
    float onXaxis = step(0.0, st.x) * step(st.x, thickness);
    float onYaxis = step(0.0, st.y) * step(st.y, thickness);

    return max(onXaxis, onYaxis);
}

void main() {
//    float scale = 100.0;
//    float numTiles = 2.0;
//    float res = numTiles / scale;
//
//    vec2 grid_uv = aPos.xy * scale;
//    float x = grid(grid_uv, res);
//    float axisColor = axis(aPos.xy, 1.0 / scale);
//
//    FragColor.rgb = vec3(0.5) * x;
//    FragColor.r = axisColor;
//    FragColor.a = 1.0;
    FragColor = vec4(1.0, 0.0, 1.0, 1.0);
}