#version 420

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in VS_OUT {
  vec3 Pos;
  float Size;
} gs_in[];

uniform vec3 CameraUp;
uniform vec3 CameraRight;
uniform mat4 VP;
uniform mat4 World;

void main() {    
  gl_Position = (World * VP) * vec4(gs_in[0].Pos + (+CameraUp - CameraRight) * gs_in[0].Size, 1);
  EmitVertex();

  gl_Position = (World * VP) * vec4(gs_in[0].Pos + (+CameraUp + CameraRight) * gs_in[0].Size, 1);
  EmitVertex();

  gl_Position = (World * VP) * vec4(gs_in[0].Pos + (-CameraUp - CameraRight) * gs_in[0].Size, 1);
  EmitVertex();

  gl_Position = (World * VP) * vec4(gs_in[0].Pos + (-CameraUp + CameraRight) * gs_in[0].Size, 1);
  EmitVertex();


  EndPrimitive();
} 
