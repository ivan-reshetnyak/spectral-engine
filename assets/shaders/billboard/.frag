#version 420

in GS_OUT {
  vec2 Tex;
} fs_in;

out vec4 OutCol;

uniform sampler2D Texture;

void main( void ) {
  OutCol = texture2D(Texture, fs_in.Tex);
}
