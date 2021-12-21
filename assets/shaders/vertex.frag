#version 330
layout (location = 0) in vec3 aPos;
out vec3 v_uv;
//layout (location = 1) in vec2 aTexCoord;
//out vec2 texCoord;

//uniform mat4 model;
//uniform mat4 view;
//uniform mat4 projection;
uniform mat4 model;

void main() {
  v_uv = aPos;
  gl_Position = model * vec4(aPos, 1.0f);
//    gl_Position = projection * view * model * vec4(aPos, 1.0f);
//    texCoord = vec2(aTexCoord.x, aTexCoord.y);
}
