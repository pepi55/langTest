#version 330 core

layout(location = 0) in vec3 vertexPosition_trianglespace;
layout(location = 1) in vec3 vertexPosition_cubespace;
layout(location = 2) in vec3 vertexColor;

out vec3 fragmentColor;

uniform mat4 MVP;

void main () {
	gl_Position = MVP * vec4(vertexPosition_trianglespace, 1);
	fragmentColor = vertexColor;
}
