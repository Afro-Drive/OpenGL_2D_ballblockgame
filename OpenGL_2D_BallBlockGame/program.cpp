/*****************************************************************************
** This code is root file of OpenGL 2D Ball Brock Game.
** When this game runs, proceed this cpp at first.
******************************************************************************/

#include<iostream>
#include<glad/gl.h>
#include<GLFW/glfw3.h>

#include"game.h"
#include"resourceManager.h"


// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The Height of the screen
const unsigned int SCREEN_HEIGHT = 600;

Game BrockBallGame(SCREEN_WIDTH, SCREEN_HEIGHT);


// GLFW function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

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

	// glad: load all OpenGL function pointers
	// -----------------------------------------
	if (!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// OpenGL configuration
	// ---------------------
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// initialize game
	// ---------------
	BrockBallGame.Init();

	// deltaTime variables
	// -------------------
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;


	// main game loop
	while (!glfwWindowShouldClose(window))
	{
		// calculate delta time
		// --------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();

		// manage user input
		// -----------------
		BrockBallGame.ProcessInput(deltaTime);

		// update game state
		// -----------------
		BrockBallGame.Update(deltaTime);

		// render
		// ------
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		BrockBallGame.Render();

		glfwSwapBuffers(window);
	}

	// delete all resources al loaded using the resource manager
	// ---------------------------------------------------------
	ResourceManager::Clear();

	// Destroy Window
	glfwDestroyWindow(window);
	// termination GLFW
	glfwTerminate();

	// Finished correctly
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			BrockBallGame.Keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			BrockBallGame.Keys[key] = false;
			BrockBallGame.KeysProcessed[key] = false;
		}
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions. note that width and
	// height will be significantly larger than specified on retina displays
	glViewport(0, 0, width, height);
}