#version 410
// Instruction au cas ou la version 410 ne marcherait pas
//#version 300 es
//precision mediump float


layout(location=0) in vec3 vx_pos; // Indice 0
layout(location=2) in vec2 vx_uvs; // Indice 2

uniform mat4 projectionMat;
uniform mat4 modelviewMat;

out vec2 uvs;
out vec3 pos;

void main()
{
	pos = vx_pos;
	gl_Position = projectionMat*modelviewMat*vec4(vx_pos,1.0);
	//gl_Position = projectionMat*vec4(vx_pos,1.0);
	//gl_Position = vec4(vx_pos,1.0);
	uvs = vx_uvs;
	//color = vec3(1.0,1.0,0.0);
}
