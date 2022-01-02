#version 330
out vec4 FragColor;
in float fOpacity;

void main() {
  if (fOpacity < 0.1) discard;

  FragColor =  vec4(0.0, 0.6, 0.0, 1.0);
}
