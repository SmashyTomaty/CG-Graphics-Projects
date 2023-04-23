#pragma once
#include "GLFW/glfw3.h"
#include "Object3D.h"
#include "Plane.h"
#include "Cube.h"
#include <vector>

class Application 
{
public:
	Application();

	void key_callback(int key, int scancode, int action, int mods);
	void mouse_callback(double xpos, double ypos);

	void Setup();

	void Update();

	void Draw();

	void Terminate();

	void DrawLaberynth();
	void DrawPills();

	//GLFWwindow* GetWindow() { return window; }

	GLFWwindow* window;

private:

	Object3D dummy;
	Plane plane;
	Cube cube;
	Cube pill;

	float fTime = 0;
	glm::mat4 mouseRotateX, mouseRotateY;
	float lastX = 1080 / 2;
	float lastY = 720 / 2;
	float yaw = -90.0f;
	float realyaw = -90.0f;
	float addyaw = 0.0f;
	float pitch = 0.0f;
	float winCountdown = 0;
	float currentlab = 0;

	glm::vec3 camPos = glm::vec3(-0.5f, 0.0f, 0.0f);
	glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 walkFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 hintUp = glm::vec3(0.0f, 1.0f, 0.0f);
	std::vector<std::vector<std::vector<char>>> ls;


	GLuint loadTexture(const std::string& filename);
};