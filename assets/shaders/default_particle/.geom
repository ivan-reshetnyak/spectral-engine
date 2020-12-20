#version 420

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in VS_OUT {
  vec3 Pos;
  float Size;
} gs_in[];

out GS_OUT {
  vec2 Tex;
} gs_out;

uniform float Rotation;
uniform vec3 CameraUp;
uniform vec3 CameraPos;
uniform vec3 CameraRight;
uniform mat4 VP;
uniform mat4 World;

void main() {
  vec3 Shift;
  float R = Rotation;

  Shift = +CameraUp * sin(R) + CameraRight * cos(R);
  gl_Position = (World * VP) * vec4(gs_in[0].Pos + Shift.xyz * gs_in[0].Size, 1);
  gs_out.Tex = vec2(0, 1);
  EmitVertex();

  R += 3.14159265358979323846 * 0.5;
  Shift = +CameraUp * sin(R) + CameraRight * cos(R);
  gl_Position = (World * VP) * vec4(gs_in[0].Pos + Shift.xyz * gs_in[0].Size, 1);
  gs_out.Tex = vec2(1, 1);
  EmitVertex();

  R += 3.14159265358979323846;
  Shift = +CameraUp * sin(R) + CameraRight * cos(R);
  gl_Position = (World * VP) * vec4(gs_in[0].Pos + Shift.xyz * gs_in[0].Size, 1);
  gs_out.Tex = vec2(0, 0);
  EmitVertex();

  R -= 3.14159265358979323846 * 0.5;
  Shift = +CameraUp * sin(R) + CameraRight * cos(R);
  gl_Position = (World * VP) * vec4(gs_in[0].Pos + Shift.xyz * gs_in[0].Size, 1);
  gs_out.Tex = vec2(1, 0);
  EmitVertex();

  EndPrimitive();
}
