#version 420

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in VS_OUT {
  vec2 V0, V1;
  float Value;
} gs_in[];


out GS_OUT {
  vec2 Tex;
} gs_out;


void main() {
  gl_Position = vec4(gs_in[0].V0.x, gs_in[0].V1.y, 0, 1);
  gs_out.Tex = vec2(gs_in[0].Value * 0.1, 0);
  EmitVertex();

  gl_Position = vec4(gs_in[0].V1.x, gs_in[0].V1.y, 0, 1);
  gs_out.Tex = vec2(gs_in[0].Value * 0.1 + 0.1, 0);
  EmitVertex();

  gl_Position = vec4(gs_in[0].V0.x, gs_in[0].V0.y, 0, 1);
  gs_out.Tex = vec2(gs_in[0].Value * 0.1, 1);
  EmitVertex();

  gl_Position = vec4(gs_in[0].V1.x, gs_in[0].V0.y, 0, 1);
  gs_out.Tex = vec2(gs_in[0].Value * 0.1 + 0.1, 1);
  EmitVertex();

  EndPrimitive();
}
