#version 450

in vec3 vColor;
out vec4 outColor;

void main (void) {
  outColor = vec4(vColor.xyz, 1);
}