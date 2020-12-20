#version 420

in GS_OUT {
  vec2 Tex;
} fs_in;

out vec4 OutCol;

uniform sampler2D Texture;

uniform vec4 Color;
uniform float LifeTime;
uniform float t;

void main( void ) {
  vec4 Tex = texture2D(Texture, fs_in.Tex);
  OutCol = vec4(Color.rgb * Tex.rgb, Color.a * Tex.a * (1.0 - t / LifeTime));
}
