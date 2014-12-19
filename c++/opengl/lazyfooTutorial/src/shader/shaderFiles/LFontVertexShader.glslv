#version 330

uniform mat4 LProjectionMatrix;
uniform mat4 LModelViewMatrix;

in vec2 LVertexPos2D;

in vec2 LTexCoord;
out vec2 texCoord;

void main(void) {
	texCoord = LTexCoord;

	gl_Position = LProjectionMatrix * LModelViewMatrix * vec4(LVertexPos2D.x, LVertexPos2D.y, 0.0, 1.0);
}
