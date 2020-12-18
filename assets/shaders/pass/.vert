#version 420

layout (location = 0) in vec3 InPos;
layout (location = 1) in vec3 InNorm;
layout (location = 2) in vec4 InCol;
layout (location = 3) in vec2 InTex;

out vec3 Pos;
out vec3 Norm;
out vec4 Col;
out vec2 Tex;

uniform float Time;

void main( void ) {
  Pos = InPos;
  Norm = InNorm;
  Col = InCol;
  Tex = InTex;

  gl_Position = vec4(Pos, 1); 
}