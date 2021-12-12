#version 330

out vec4 FragColor;

uniform vec3 color;

//in vec2 texCoord;
//uniform sampler2D texture1;
//uniform sampler2D texture2;

void main() {
//    FragColor = texture(texture1, texCoord);
//    FragColor = mix(
//        texture(texture1, texCoord),
//        texture(texture2, texCoord),
//        0.2
//    );

    FragColor = vec4(color, 1.0f);


}