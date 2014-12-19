#version 330

uniform vec4 LTextColor;
uniform sampler2D LTextureUnit;

in vec2 texCoord;
out vec4 gl_FragColor;

void main(void) {
	gl_FragColor = texture(LTextureUnit, texCoord) * LTextColor;
}
