/*****************************************************************************
** This code is root file of OpenGL 2D Ball Brock Game.
** When this game runs, proceed this cpp at first.
******************************************************************************/

#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>

// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The Height of the screen
const unsigned int SCREEN_HEIGHT = 600;


// main function
int main()
{
	// Initialize GLFW library
	glfwInit();

	// Tell GLFW meta configurations
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create Window
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL 2D Ball Brock Game!", NULL, NULL);
	// Early guard statement in case of failure creation of window
	// Terminate as failure
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Tell GLFW current window
	glfwMakeContextCurrent(window);

	gladLoadGL(glfwGetProcAddress);

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// main game loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}

	// Destroy Window
	glfwDestroyWindow(window);
	// termination GLFW
	glfwTerminate();

	// Finished correctly
	return 0;
}