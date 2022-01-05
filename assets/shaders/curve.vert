#version 330
layout (location = 0) in vec2 aPos;
layout (location = 1) in float timeStep;

out float tStep;

void main() {
  tStep = timeStep;
  gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);
}
