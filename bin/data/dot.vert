#version 450
layout(location=0) in vec3 aVertex;
layout(location=5) in vec3 aPosition;
layout(location=6) in vec3 aScale;
layout(location=7) in vec3 aColor;

//uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
out vec3 vColor;

void main(void) {
  //vec4 position = modelViewProjectionMatrix * vec4(aVertex+aPosition, 1);
  mat4 scaled = mat4(
      vec4(aScale.x, 0, 0, 0),
      vec4(0, aScale.y, 0, 0),
      vec4(0, 0, aScale.z, 0),
      vec4(0, 0, 0, 1)
  );
  //scaled[0][0] = aScale.x;
  //scaled[1][1] = aScale.y;
  //scaled[2][2] = aScale.z;
  mat4 transformed = modelMatrix * scaled;
  mat4 mvp = projectionMatrix * viewMatrix * transformed;
  vec4 position = mvp * vec4((aVertex+aPosition), 1);
  vColor = aColor;
  gl_Position = position;
}