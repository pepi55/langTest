#version 120

uniform mat4 LProjectionMatrix;
uniform mat4 LModelViewMatrix;

void main(void) {
	gl_Position = LProjectionMatrix * LModelViewMatrix * gl_Vertex;
}
