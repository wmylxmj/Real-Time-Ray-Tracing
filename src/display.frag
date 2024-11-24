#version 430 core

uniform sampler2D frame;
in vec2 pixel;
out vec4 FragColor;

void main() {
    vec3 color = texture2D(frame, pixel.xy * 0.5 + 0.5).rgb;
    color = pow(color, vec3(1.0 / 2.2));
    FragColor = vec4(color, 1.0);
}
