#pragma once
#include <vector>
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

	void MakePlane(float size);

private:

	Object3D triangle;
	float fTime = 0;
	glm::mat4 accum;
	GLuint fTime_id; //we use IDs to alocate space to transfer info from GL to Lenguage.
	GLuint accum_id;
	std::vector<glm::vec4> planeVerts;
	std::vector<glm::vec4> planeColor;
};