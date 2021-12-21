#version 330

out vec4 FragColor;
in vec4 v_uv; 

//in vec2 texCoord;
//uniform sampler2D texture1;
//uniform sampler2D texture2;

float grid(vec2 st, float res) {
    vec2 grid = fract(st*res);
    return 1.0 - (step(res, grid.x) * step(res, grid.y));
}

float axis(vec2 st, float thickness) {
    float onXaxis = step(0.0, st.x) * step(st.x, thickness);
    float onYaxis = step(0.0, st.y) * step(st.y, thickness);

    return max(onXaxis, onYaxis);
}

void main() {
  //vec3 v_uv = gl_FragCoord.xyz;
  float SCALE = 100.0;
  float NUM_TILES = 3.5;
  float res = NUM_TILES / SCALE;

  vec2 grid_uv = v_uv.xy * SCALE;
  float x = grid(grid_uv, res);
  float axisColor = axis(v_uv.xy, 1.0 / SCALE);

  FragColor.rgb = vec3(0.5) * x;
  FragColor.r = axisColor;
  FragColor.a = 1.0;
  FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);
}
