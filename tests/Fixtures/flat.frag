#version 450
layout(location = 0) out vec4 color;
layout(set = 3, binding = 0) uniform Fill { vec4 rgba; };
void main() { color = rgba; }
