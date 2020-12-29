#version 420

out VS_OUT {
  vec3 Pos;
} vs_out;


uniform vec3 p0;
uniform vec3 v0;
uniform float t;
uniform float g;
uniform vec3 Wind;

void main( void ) {
  vec3 a = vec3(0, g, 0) + Wind;
  vs_out.Pos = p0 + v0 * t + a * t * t * 0.5;
}
