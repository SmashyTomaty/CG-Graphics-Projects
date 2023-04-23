#pragma once
#include "GLFW/glfw3.h"
#include "Object3D.h"
#include "Plane.h"
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

	//GLFWwindow* GetWindow() { return window; }

	GLFWwindow* window;

private:

	Object3D triangle;
	Plane plane;

	float fTime = 0;
	glm::mat4 mouseRotateX, mouseRotateY;

	std::map<std::string, GLuint> uniforms; //we use IDs to alocate space to transfer info from GL to Lenguage.
	std::map<std::string, glm::mat4> matrixes;

	glm::vec3 camMoveDir;
	glm::vec3 camPos = glm::vec3(0,0,10);
	glm::vec3 camFront = glm::vec3(0, 0, -1);

	GLuint loadTexture(const std::string& filename);
};