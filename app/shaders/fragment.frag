#version 330

out vec4 FragColor;
in vec3 v_uv;

//in vec2 texCoord;
//uniform sampler2D texture1;
//uniform sampler2D texture2;

float grid(vec2 st, float res) {
  vec2 grid = fract(st*res);
  return (step(res,grid.x) * step(res,grid.y));
}

float axis(vec2 st, float thickness) {
  return step(-thickness, st.x) * step(st.x, thickness);
}
void main() {
  vec2 grid_uv = v_uv.xy * 50.0; // scale
  float x = grid(grid_uv, 0.1); // resolution
  float yAxis = axis(v_uv.xy * 50.0, 0.15);
  
  FragColor.rgb = vec3(0.5) * x;
  FragColor.r = yAxis;
  FragColor.a = 1.0;
}
