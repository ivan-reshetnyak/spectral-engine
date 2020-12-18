#version 420

in vec3 Pos;
in vec3 Norm;
in vec4 Col;
in vec2 Tex;

out vec4 OutCol;

void main( void ) {
  OutCol = Col;
}