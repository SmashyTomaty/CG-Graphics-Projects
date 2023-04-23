#include <iostream>
#include <vector>

#include "GL/glew.h"
#include <GL/GL.h>
#include <GL/GLU.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4X4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"

#include "ShaderFuncs.h"
#include "Application.h"
#include "Laberynths.h"

std::vector<std::vector<char>> Laberynth{

};

Application::Application()
{

}

void Application::key_callback(int key, int scancode, int action, int mods)
{
	float camSpeed = 0.02f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		yaw = realyaw;
		addyaw = 0;
		addyaw = -90.0;
		realyaw -= 90.0;
		//camPos -= glm::normalize(glm::cross(camFront, hintUp)) * camSpeed;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		yaw = realyaw;
		addyaw = 0;
		addyaw = 90.0;
		realyaw += 90.0;
		//camPos += glm::normalize(glm::cross(camFront, hintUp)) * camSpeed;
	}
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		//camPos += camSpeed * camFront;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		yaw = realyaw;
		addyaw = 0;
		addyaw = -180.0;
		realyaw -= 180.0;
		//camPos -= camSpeed * camFront;
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
		glfwSetWindowShouldClose(window, 1);
	}

	if (key == GLFW_KEY_I && action == GLFW_REPEAT) {
		fTime += 1;
	} else if(key == GLFW_KEY_K && action == GLFW_REPEAT) {
		fTime -= 1;
	}
}

void Application::mouse_callback(double xpos, double ypos)
{
	float xof = xpos - lastX;
	float yof = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.3f;
	xof *= sensitivity;
	yof *= sensitivity;

	//yaw += xof;
	pitch += yof;

	if (pitch > 45.0f) {
		pitch = 45.0f;
	}
	else if (pitch < -45.0f) {
		pitch = -45.0f;
	}

	mouseRotateX = glm::rotate(glm::mat4(1), (float)glm::radians(yaw), glm::vec3(0, 1, 0));
	mouseRotateY = glm::rotate(glm::mat4(1), (float)glm::radians(pitch), glm::vec3(1, 0, 0));
}

GLuint Application::loadTexture(const std::string& filename)
{
	int w, h, chan;
	unsigned char* data{ nullptr };
	data = stbi_load(filename.c_str(), &w, &h, &chan, 0);
	GLuint texID = 0;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D, 0);
	return texID;
}

void Application::Setup()
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	ls = makeLaberynths();
	Laberynth = ls[currentlab];
	std::string strVertexShader = loadTextFile("Shaders/NormalMaps.vert");
	std::string strFragmentShader = loadTextFile("Shaders/NormalMaps.frag");

	InitializeProgram(cube.shader, strVertexShader, strFragmentShader);
	cube.MakeCube();
	cube.Object3DSetup(2);

	GLint id2 = loadTexture("Assets/RockN.png");
	if (id2 > 0) {
		cube.textureIDs.push_back(id2);
	}

	id2 = loadTexture("Assets/Rock.png");
	if (id2 > 0) {
		cube.textureIDs.push_back(id2);
	}

	InitializeProgram(plane.shader, strVertexShader, strFragmentShader);
	plane.MakePlane(1);
	plane.Object3DSetup(2);

	GLint id = loadTexture("Assets/TileN.png");
	if (id > 0) {
		plane.textureIDs.push_back(id);
	}

	id = loadTexture("Assets/Tile.jpg");
	if (id > 0) {
		plane.textureIDs.push_back(id);
	}

	strVertexShader = loadTextFile("Shaders/PassThru.vert");
	strFragmentShader = loadTextFile("Shaders/PassThru.frag");

	InitializeProgram(pill.shader, strVertexShader, strFragmentShader);
	pill.MakeCube();
	pill.Object3DSetup(2);

	GLint id3 = loadTexture("Assets/TileN.png");
	if (id3 > 0) {
		pill.textureIDs.push_back(id3);
	}
	id3 = loadTexture("Assets/Pills.jpg");
	if (id3 > 0) {
		pill.textureIDs.push_back(id3);
	}
}

void Application::Update()
{
	glUseProgram(plane.shader);
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0, -3, 0));
	glm::mat4 rotet = glm::rotate(glm::mat4(1), glm::radians(-270.0f), glm::vec3(1, 0, 0));
	glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(15, 15, 15));
	plane.Object3DSetMatrix(fTime, camPos, camFront, hintUp, translate, rotet, scale);


	if (addyaw != 0) {
		if (addyaw <= -1) {
			yaw -= 10;
			addyaw += 10;
		}
		if (addyaw >= 1) {
			yaw += 10;
			addyaw -= 10;
		}
	}
	glm::vec3 dir;
	dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	dir.y = sin(glm::radians(pitch));
	dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camFront = glm::normalize(dir);

	dir.x = cos(glm::radians(realyaw));
	dir.z = sin(glm::radians(realyaw));
	walkFront = glm::normalize(dir);

	float offset = 2.0f;
	if (camPos.x < 0) {
		offset = 1.0f;
	}

	if (camPos.z > 7) {
		offset = 1.5f;
		if (camPos.z > 10) {
			offset = 2.0f;
		}
	}

	float camSpeed = 0.2f;

	glm::vec3 playerPos = glm::vec3((int)(camPos.x + (offset * walkFront.x)), -2, (int)(camPos.z + (offset * walkFront.z)));
	glm::vec3 laberynthPos = glm::vec3(((1 + playerPos.x) / 2) + 7, 0, ((1.5 + playerPos.z) / 2) + 7);
	if (Laberynth[laberynthPos.x][laberynthPos.z] != 1) {
		camPos += camSpeed * walkFront;
	}
	
	if (Laberynth[laberynthPos.x][laberynthPos.z] == 2) {
		Laberynth[laberynthPos.x][laberynthPos.z] = 0;
	}
	camPos.y = 0;

}

void Application::Draw()
{
	glClearColor(0.0f, 0.0f, 0.2f, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (winCountdown < 1) {
		glUseProgram(plane.shader);
		plane.Object3DSetDraw(2);
		plane.DrawPlane();

		glUseProgram(cube.shader);

		cube.Object3DSetDraw(2);
		DrawLaberynth();

		glUseProgram(pill.shader);
		pill.Object3DSetDraw(2);
		DrawPills();
	}
	else {
		winCountdown -= 1;
	}

	fTime += 0.1f;
}

void Application::DrawLaberynth() {

	for (int row = 0; row < Laberynth.size(); ++row) {
		for (int col = 0; col < Laberynth.size(); ++col) {

			glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(-15 + row * 2, -2, -15 + col * 2));
			if (Laberynth[row][col] == 1) {
				cube.Object3DSetMatrix(fTime, camPos, camFront, hintUp, translate, glm::mat4(1), glm::mat4(1));
				cube.DrawCube();
			}
		}
	}
}

void Application::DrawPills() {

	bool pills = false;
	for (int row = 0; row < Laberynth.size(); ++row) {
		for (int col = 0; col < Laberynth.size(); ++col) {

			glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(-15 + row * 2, -2, -15 + col * 2));
			if (Laberynth[row][col] == 2) {

				glm::mat4 rotet = glm::rotate(glm::mat4(1), fTime + row + col / 2, glm::vec3(0.5, 0.5, 0));
				glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(0.5, 0.5, 0.5));
				pill.Object3DSetMatrix(fTime, camPos, camFront, hintUp, translate, rotet, scale);
				pill.DrawCube();
				pills = true;
			}
		}
	}

	if (pills == false) {
		winCountdown = 170;
		currentlab += 1;
		if (currentlab > ls.size() -1) { currentlab = 0; }
		Laberynth = ls[currentlab];
		camPos = glm::vec3(-0.5f,0,0);
	}
}

void Application::Terminate()
{
	//OOOO I AM THE TERMINATOR PEW PEW PEW PEW PUUUSHHHAAAAAAA BOOOOOOOOOOOOOOOM PI PI PI KWHAAAAAAAAAAAAAAAAAAA "AAAAAAH!" 
	//Skynet Skynet.
}
