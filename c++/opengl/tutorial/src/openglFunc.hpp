#pragma once

//Includes
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//Constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 400;
const char *WINDOW_TITLE = "Generic Title";

//Variables
GLFWwindow *window;

//Functions
int GLFWInitialization (int samples) {
	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW!\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, samples);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

	if (window == NULL) {
		fprintf(stderr, "Failed to create GLFW window!\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = true;

	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW!\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	return 0;
}

void mainLoop (void) {
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	do {
		//Draw stuff

		glfwSwapBuffers(window);
		glfwPollEvents();
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
}
