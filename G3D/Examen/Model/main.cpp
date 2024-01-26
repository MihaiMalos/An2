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

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

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

void RenderScene(const Shader& shader);
void RenderObject();
void RenderFloor();
unsigned int CreateTexture(const std::string& strTexturePath);

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
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
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

	if (key == GLFW_KEY_INSERT && action == GLFW_PRESS)
	{
		lampCircleRadius += 1.0f;
	}
	if (key == GLFW_KEY_DELETE && action == GLFW_PRESS)
	{
		lampCircleRadius -= 1.0f;
		if (lampCircleRadius < 1.0f) lampCircleRadius = 1.0f;
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

	// Create camera
	pCamera = new Camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0, 0.0, 3.0));
	Shader shadowMappingShader("ShadowMapping.vs", "ShadowMapping.fs");
	Shader shadowMappingDepthShader("ShadowMappingDepth.vs", "ShadowMappingDepth.fs");

	unsigned int floorTexture = CreateTexture(R"(Resources/floor.png)");

	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	// create depth texture
	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	// attach depth texture as FBO's depth buffer
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// shader configuration
	shadowMappingShader.Use();
	shadowMappingShader.SetInt("diffuseTexture", 0);
	shadowMappingShader.SetInt("shadowMap", 1);

	// lightning info
	glEnable(GL_CULL_FACE);

	// render loop
	while (!glfwWindowShouldClose(window)) {

		// per-frame time logic

		double currentFrame = glfwGetTime();

		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		lightPos = glm::vec3(sin(currentFrame) * lampCircleRadius, 0, cos(currentFrame) * lampCircleRadius);

		// input

		processInput(window);

		// Render
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 1. render depth of scene to texture (from light's perspective)
		glm::mat4 lightProjection, lightView;
		glm::mat4 lightSpaceMatrix;
		float near_plane = 1.0f, far_plane = 7.5f;
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
		lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
		lightSpaceMatrix = lightProjection * lightView;

		// render scene from light's point of view
		shadowMappingDepthShader.Use();
		shadowMappingDepthShader.SetMat4("lightSpaceMatrix", lightSpaceMatrix);

		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, floorTexture);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		RenderScene(shadowMappingDepthShader);
		glCullFace(GL_BACK);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		// reset viewport
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// 2. render scene as normal using the generated depth/shadow map 
		glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shadowMappingShader.Use();
		glm::mat4 projection = pCamera->GetProjectionMatrix();
		glm::mat4 view = pCamera->GetViewMatrix();
		shadowMappingShader.SetMat4("projection", projection);
		shadowMappingShader.SetMat4("view", view);
		// set light uniforms
		shadowMappingShader.SetVec3("viewPos", pCamera->GetPosition());
		shadowMappingShader.SetVec3("lightPos", lightPos);
		shadowMappingShader.SetMat4("lightSpaceMatrix", lightSpaceMatrix);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, floorTexture);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		glDisable(GL_CULL_FACE);
		RenderScene(shadowMappingShader);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	Cleanup();

	// glfw: terminate, clearing all previously allocated GLFW resources
	glfwTerminate();

	return 0;

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly

void RenderScene(const Shader& shader)
{
	// floor
	glm::mat4 model = glm::mat4(1);
	shader.SetMat4("model", model);
	RenderFloor();

	// object
	model = glm::translate(glm::mat4(1.0), objectPos);
	if (xrotation || yrotation || zrotation)
	{
		model = glm::rotate(model, (float)glm::radians(500 * glfwGetTime()),
				glm::vec3(xrotation ? 1.f : 0.f, yrotation ? 1.f : 0.f, zrotation ? 1.f : 0));
	}
	model = glm::scale(model, objectScale);
	model = glm::scale(model, glm::vec3(1, objectHeight, 1));
	shader.SetMat4("model", model);
	RenderObject();

	// render light source object
	model = glm::translate(glm::mat4(1.0f), lightPos);
	model = glm::scale(model, glm::vec3(0.05f));
	shader.SetMat4("model", model);
	RenderObject();


}

unsigned int objectVAO = 0;
unsigned int objectVBO = 0;
unsigned int objectIBO = 0;
void RenderObject() 
{
	static float width = 5, length = 5, height = 1;

	width /= 2.0f;
	length /= 2.0f;
	/*height /= 2.0f;*/

	static float vertices[] = {
		-width / 2.0f,         0,   -length,   0, 1, 0,
		 width / 2.0f,         0,   -length,   0, 1, 0,
		 width,                0,         0,   0, 1, 0,
			 0,                0,    length,   0, 1, 0,
		-width,                0,         0,   0, 1, 0,

		-width / 2.0f,    height,   -length,   0, 1, 0,
		 width / 2.0f,    height,   -length,   0, 1, 0,
		 width,           height,         0,   0, 1, 0,
			 0,           height,    length,   0, 1, 0,
		-width,           height,         0,   0, 1, 0,
	};

	static unsigned int indices[] = {
		4,2,3,
		0,1,4,
		4,1,2,

		9,7,8,
		5,6,9,
		9,6,7,

		0,1,5,
		5,1,6,

		2,1,6,
		6,2,7,

		8,3,2,
		8,2,7,

		9,8,4,
		4,8,3,

		4,0,9,
		9,0,5,
	};

	if (objectVAO == 0)
	{
		// Generate buffers and arrays
		glGenVertexArrays(1, &objectVAO);
		glGenBuffers(1, &objectVBO);
		glGenBuffers(1, &objectIBO);

		// Bind VAO
		glBindVertexArray(objectVAO);

		// Bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, objectVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Bind EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objectIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Set vertex attribute pointers
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	glBindVertexArray(objectVAO);
	glBindBuffer(GL_ARRAY_BUFFER, objectVBO);
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

unsigned int planeVAO = 0;
void RenderFloor()
{
	unsigned int planeVBO;

	if (planeVAO == 0) {
		// set up vertex data (and buffer(s)) and configure vertex attributes
		float planeVertices[] = {
			// positions            // normals         // texcoords
			25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
			-25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
			-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,

			25.0f, -0.5f,  25.0f,  0.0f, 1.0f, 0.0f,  25.0f,  0.0f,
			-25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,   0.0f, 25.0f,
			25.0f, -0.5f, -25.0f,  0.0f, 1.0f, 0.0f,  25.0f, 25.0f
		};
		// plane VAO
		glGenVertexArrays(1, &planeVAO);
		glGenBuffers(1, &planeVBO);
		glBindVertexArray(planeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glBindVertexArray(0);
	}

	glBindVertexArray(planeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


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

unsigned int CreateTexture(const std::string& strTexturePath)
{
	unsigned int textureId = -1;

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char* data = stbi_load(strTexturePath.c_str(), &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else {
		std::cout << "Failed to load texture: " << strTexturePath << std::endl;
	}
	stbi_image_free(data);

	return textureId;
}