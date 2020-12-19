#version 420

layout (location = 0) in vec3 InPos;
layout (location = 1) in float InSize;

out VS_OUT {
  out vec3 Pos;
  out float Size;
} vs_out;


uniform float Time;

void main( void ) {
  vs_out.Pos = InPos;
  vs_out.Size = InSize;
  gl_Position = vec4(vs_out.Pos, 1); 
}
