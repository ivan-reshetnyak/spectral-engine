#version 420

#define Pi 3.14159265358979323846

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in VS_OUT {
  vec3 Pos;
} gs_in[];


out GS_OUT {
  vec2 Tex;
} gs_out;

uniform float Rotation;
uniform float Size;

uniform vec3 CameraUp;
uniform vec3 CameraRight;

uniform mat4 VP;
uniform mat4 World;

void main() {
  vec3 Shift;
  float R = Rotation;

  Shift = +CameraUp * sin(R) + CameraRight * cos(R);
  gl_Position = (World * VP) * vec4(gs_in[0].Pos + Shift.xyz * Size, 1);
  gs_out.Tex = vec2(0, 1);
  EmitVertex();

  R += Pi * 0.5;
  Shift = +CameraUp * sin(R) + CameraRight * cos(R);
  gl_Position = (World * VP) * vec4(gs_in[0].Pos + Shift.xyz * Size, 1);
  gs_out.Tex = vec2(1, 1);
  EmitVertex();

  R += Pi;
  Shift = +CameraUp * sin(R) + CameraRight * cos(R);
  gl_Position = (World * VP) * vec4(gs_in[0].Pos + Shift.xyz * Size, 1);
  gs_out.Tex = vec2(0, 0);
  EmitVertex();

  R -= Pi * 0.5;
  Shift = +CameraUp * sin(R) + CameraRight * cos(R);
  gl_Position = (World * VP) * vec4(gs_in[0].Pos + Shift.xyz * Size, 1);
  gs_out.Tex = vec2(1, 0);
  EmitVertex();

  EndPrimitive();
}
