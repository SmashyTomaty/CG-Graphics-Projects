#pragma once
#include "GLFW/glfw3.h"
#include "Object3D.h"

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
	float fTime = 0;
	glm::mat4 accum;
	GLuint fTime_id; //we use IDs to alocate space to transfer info from GL to Lenguage.
	GLuint accum_id;

	glm::vec3 camMoveDir;
	glm::vec3 camPos = glm::vec3(0,0,10);
	glm::vec3 camFront = glm::vec3(0, 0, -1);

	GLuint loadTexture(const std::string& filename);
};