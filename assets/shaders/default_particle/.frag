#version 420

in GS_OUT {
  vec2 Tex;
} fs_in;

out vec4 OutCol;

uniform sampler2D Texture;

uniform float LifeTime;
uniform float Age;

void main( void ) {
  vec4 Tex = texture2D(Texture, fs_in.Tex);
  vec3 Col = vec3(1, 1, 1) * Tex.rgb;
  OutCol = vec4(Col, Tex.a * max(0, 1.0 - Age * 2 / LifeTime));
}
