#version 420

in vec3 Pos;
in vec3 Norm;
in vec4 Col;
in vec2 Tex;

out vec4 OutCol;

uniform vec4 Ka;
uniform vec4 Kd;
uniform vec4 Ks;

uniform float Time;

void main( void ) {
  gl_FragColor = vec4(1, 1, 1, 1);
  // gl_FragColor = Ka * Col;
}