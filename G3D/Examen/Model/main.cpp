// Lab7 - Iluminare Phong simpla.cpp : Defines the entry point for the console application.

//

#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GLM.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Camera.h"
#include "Shader.h"

#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OpenGL32.lib")

// settings

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;



GLuint ProjMatrixLocation, ViewMatrixLocation, WorldMatrixLocation;

Camera* pCamera = nullptr;

void Cleanup()
{

	delete pCamera;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// timing

double deltaTime = 0.0f;        // time between current frame and last frame
double lastFrame = 0.0f;

double objectHeight = 1.0f;
glm::vec3 objectPos = glm::vec3(0, -0.5, 0);
glm::vec3 objectScale = glm::vec3(0.3f);
bool xrotation = false, yrotation = false, zrotation = false;
double lampCircleRadius = 0.5f;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)

{

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		objectHeight *= 2;
	}
	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		objectHeight /= 2;
	}

	if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
	{
		objectScale *= 2;
	}
	if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
	{
		objectScale /= 2;
	}

	if (key == GLFW_KEY_X && action == GLFW_PRESS)
	{
		xrotation = !xrotation;
	}
	if (key == GLFW_KEY_Y && action == GLFW_PRESS)
	{
		yrotation = !yrotation;
	}
	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
	{
		zrotation = !zrotation;
	}

}


int main()

{

	// glfw: initialize and configure

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lab 7", NULL, NULL);

	if (window == NULL) {

		std::cout << "Failed to create GLFW window" << std::endl;

		glfwTerminate();

		return -1;

	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetCursorPosCallback(window, mouse_callback);

	glfwSetScrollCallback(window, scroll_callback);

	glfwSetKeyCallback(window, key_callback);

	// tell GLFW to capture our mouse

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewInit();

	glEnable(GL_DEPTH_TEST);

	float width = 5, length = 7, height = 1;

	width /= 2.0f;
	length /= 2.0f;
	/*height /= 2.0f;*/

	float vertices[] = {
	-width,      0,        -length,  0,  1,  0,
	 width,      0,        -length,  0,  1,  0,
	-width,      0,         length,  0,  1,  0,
	 width,      0,         length,  0,  1,  0,

	-width,    height,     -length,  0,  1,  0,
	 width,    height,     -length,	 0,  1,  0,
	-width,    height,      length,	 0,  1,  0,
	 width,    height,      length,	 0,  1,  0,
	};

	unsigned int indices[] = {
		0,1,3, // bottom
		0,2,3,
		
		0,2,4, // left
		2,4,6,

		2,6,3, // front
		6,7,3,

		3,7,1, // right
		7,5,1,
		
		0,4,1, // back
		4,5,1,

		4,5,6, // top
		5,6,7
	};

	// first, configure the cube's VAO (and VBO)

	unsigned int VBO, VAO, EBO;

	// Generate buffers and arrays
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind VAO
	glBindVertexArray(VAO);

	// Bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set vertex attribute pointers
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));



	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	// note that we update the lamp's position attribute's stride to reflect the updated buffer data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	// Create camera
	pCamera = new Camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0, 0.0, 3.0));
	glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
	Shader lightingShader("PhongLight.vs", "PhongLight.fs");
	Shader lampShader("Lamp.vs", "Lamp.fs");

	

	// render loop
	while (!glfwWindowShouldClose(window)) {

		// per-frame time logic

		double currentFrame = glfwGetTime();

		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		lightPos = glm::vec3(sin(currentFrame) * lampCircleRadius, 0, cos(currentFrame) * lampCircleRadius);

		// input

		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// render the cube
		lightingShader.Use();
		lightingShader.SetVec3("objectColor", 0.5f, 1.0f, 0.31f);
		lightingShader.SetVec3("lightColor", 1.0f, 1.0f, 1.0f);
		lightingShader.SetVec3("lightPos", lightPos);
		lightingShader.SetVec3("viewPos", pCamera->GetPosition());
		lightingShader.SetMat4("projection", pCamera->GetProjectionMatrix());
		lightingShader.SetMat4("view", pCamera->GetViewMatrix());
		glm::mat4 model = glm::translate(glm::mat4(1.0), objectPos);
		if (xrotation || yrotation || zrotation)
		{
			model = glm::rotate(model, (float)glm::radians(currentFrame), 
			glm::vec3(xrotation ? 1.f : 0.f, yrotation ? 1.f : 0.f, zrotation ? 1.f : 0));
		}
		model = glm::scale(model, objectScale);
		model = glm::scale(model, glm::vec3(1, objectHeight, 1));
		lightingShader.SetMat4("model", model);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
		// also draw the lamp object

		lampShader.Use();
		lampShader.SetMat4("projection", pCamera->GetProjectionMatrix());
		lampShader.SetMat4("view", pCamera->GetViewMatrix());
		model = glm::translate(glm::mat4(1.0f), lightPos);
		model = glm::scale(model, glm::vec3(0.05f));
		lampShader.SetMat4("model", model);

		glBindVertexArray(lightVAO);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);


		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Cleanup();

	glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources
	glfwTerminate();

	return 0;

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly

void processInput(GLFWwindow* window)

{

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		pCamera->ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		pCamera->ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		pCamera->ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		pCamera->ProcessKeyboard(RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		pCamera->ProcessKeyboard(UP, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		pCamera->ProcessKeyboard(DOWN, (float)deltaTime);

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		objectPos -= glm::vec3(deltaTime, 0, 0);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		objectPos += glm::vec3(deltaTime, 0, 0);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		objectPos += glm::vec3(0, deltaTime, 0);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		objectPos -= glm::vec3(0, deltaTime, 0);


	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {

		int width, height;

		glfwGetWindowSize(window, &width, &height);

		pCamera->Reset(width, height);

	}

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes

// ---------------------------------------------------------------------------------------------

void framebuffer_size_callback(GLFWwindow* window, int width, int height)

{

	// make sure the viewport matches the new window dimensions; note that width and

	// height will be significantly larger than specified on retina displays.

	pCamera->Reshape(width, height);

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)

{

	pCamera->MouseControl((float)xpos, (float)ypos);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yOffset)

{

	pCamera->ProcessMouseScroll((float)yOffset);

}