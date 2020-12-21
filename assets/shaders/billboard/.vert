#version 420

layout (location = 0) in vec2 V0;
layout (location = 1) in vec2 V1;

out VS_OUT {
  vec2 V0, V1;
} vs_out;

void main( void ) {
  vs_out.V0 = V0;
  vs_out.V1 = V1;
}
