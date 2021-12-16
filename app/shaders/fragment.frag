#version 330

out vec4 FragColor;
in vec3 v_uv;

//in vec2 texCoord;
//uniform sampler2D texture1;
//uniform sampler2D texture2;

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
  float widthThickness = 0.1;
  float heightThickness = 0.1;

  float scale = 100.0;
  float numTiles = 2.0;
  float res = numTiles / scale;
  //float res = widthThickness * heightThickness;

  vec2 grid_uv = v_uv.xy * scale;
  float x = grid(grid_uv, res); 
  float yAxis = axis(v_uv.xy, 1.0 / scale);
  
  FragColor.rgb = vec3(0.5) * x;
  FragColor.r = yAxis;
  FragColor.a = 1.0;
}
