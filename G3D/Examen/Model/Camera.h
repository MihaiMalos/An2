#pragma once

#include <GL/glew.h>
#include <GLM.hpp>
#include <gtc/matrix_transform.hpp>

enum ECameraMovementType
{
	UNKNOWN,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera

{

private:
	// Default camera values
	const float zNEAR = 0.1f;
	const float zFAR = 500.f;
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float FOV = 45.0f;
	glm::vec3 startPosition;

public:
	Camera(const int width, const int height, const glm::vec3& position);

	void Set(const int width, const int height, const glm::vec3& position);

	void Reset(const int width, const int height);

	void Reshape(int windowWidth, int windowHeight);

	const glm::mat4 GetViewMatrix() const;

	const glm::vec3 GetPosition() const;

	const glm::mat4 GetProjectionMatrix() const;

	void ProcessKeyboard(ECameraMovementType direction, float deltaTime);

	void MouseControl(float xPos, float yPos);

	void ProcessMouseScroll(float yOffset);

private:

	void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

	void UpdateCameraVectors();

protected:

	const float cameraSpeedFactor = 0.4f;
	const float mouseSensitivity = 0.1f;
	float zNear, zFar, FoVy;

	int width, height;
	bool isPerspective;

	glm::vec3 position, forward, right, up, worldUp;

	float yaw, pitch;

	bool bFirstMouseMove = true;

	float lastX = 0.f, lastY = 0.f;

};
