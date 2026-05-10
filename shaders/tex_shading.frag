#version 410
// Instruction au cas ou la version 410 ne marcherait pas
//#version 300 es
//precision mediump float

in vec2 uvs;
in vec3 pos;
uniform samplerCube u_tex;

layout(location = 0) out vec4 final_col;

void main()
{
	//final_col = vec4(1.0,0.0,0.0,1.0);
	final_col = texture(u_tex,pos);
	//final_col = vec4(uvs,0.0,1.0);
}
