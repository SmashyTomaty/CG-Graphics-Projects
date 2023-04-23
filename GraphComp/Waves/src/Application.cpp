#include <iostream>
#include <vector>

#include "GL/glew.h"
#include <GL/GL.h>
#include <GL/GLU.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4X4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

#include "ShaderFuncs.h"
#include "Application.h"

GLfloat vertAndTextPositions[] = {
	1, 1, 0, 1.0f, 1.0f, 0.0f,
	-1, 1, 0, 1.0f, 0.0f, 0.0f,
	1, -1, 0, 1.0f, 1.0f, 1.0f,
	-1, -1, 0, 1.0f, 0.0f, 1.0f,
};

Application::Application()
{

}

void Application::key_callback(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
		glfwSetWindowShouldClose(window, 1);
	}

	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		camMoveDir = glm::vec3(-0.2f, 0, 0);
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		camMoveDir = glm::vec3(0.2f, 0, 0);
	}
	else if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		camMoveDir = glm::vec3(0, 0, -0.2f);
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		camMoveDir = glm::vec3(0, 0, 0.2f);
	}
	else {
		camMoveDir = glm::vec3(0, 0, 0);
	}

	if (key == GLFW_KEY_I && action == GLFW_REPEAT) {
		fTime += 0.1;
	} else if(key == GLFW_KEY_K && action == GLFW_REPEAT) {
		fTime -= 0.1;
	}
}

void Application::mouse_callback(double xpos, double ypos)
{
	mouseRotateX = glm::rotate(glm::mat4(1), (float)glm::radians(xpos / 2.04f), glm::vec3(0, 1, 0));
	mouseRotateY = glm::rotate(glm::mat4(1), (float)glm::radians(ypos / 2.04f), glm::vec3(1, 0, 0));
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glBindTexture(GL_TEXTURE_2D, 0);
	return texID;
}

void Application::Setup()
{
	glEnable(GL_DEPTH);
	glCullFace(GL_FRONT_AND_BACK);
	glFrontFace(GL_CCW);
	std::string strVertexShader = loadTextFile("Shaders/Phong.vert");
	std::string strFragmentShader = loadTextFile("Shaders/Phong.frag");
	InitializeProgram(plane.shader, strVertexShader, strFragmentShader);

	plane.MakePlane(60);

	glGenVertexArrays(1, &plane.vao);
	glBindVertexArray(plane.vao);
	glGenBuffers(1, &plane.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, plane.vbo);
	glBufferData(GL_ARRAY_BUFFER, plane.planeBytes + plane.planeTex, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, plane.planeBytes, (void*)&plane.planeVerts[0]);
	glBufferSubData(GL_ARRAY_BUFFER, plane.planeBytes, plane.planeTex, (void*)&plane.planeTextures[0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(plane.planeBytes));
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertAndTextPositions), vertAndTextPositions, GL_STATIC_DRAW);
	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, (4+2) * sizeof(float), 0);
	//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, (4+2) * sizeof(float), (void*)(4 * sizeof(float)));
	//Cube Stuff Commented

	glEnableVertexAttribArray(0); //enable the vertex array channel at 0
	glEnableVertexAttribArray(1);

	uniforms["fTime_id"] = glGetUniformLocation(plane.shader, "fTime");
	uniforms["accum_id"] = glGetUniformLocation(plane.shader, "accum");
	uniforms["proyection_id"] = glGetUniformLocation(plane.shader, "proyection");
	uniforms["camera_id"] = glGetUniformLocation(plane.shader, "camera");
	uniforms["eye_id"] = glGetUniformLocation(plane.shader, "eye");

	GLuint samplerID = glGetUniformLocation(plane.shader, "samp");
	if (samplerID > 0) {
		plane.samplers.push_back(samplerID);
	}

	samplerID = glGetUniformLocation(plane.shader, "texHeight");
	if (samplerID > 0) {
		plane.samplers.push_back(samplerID);
	}

	GLint id = loadTexture("Assets/Cobble_Disp.png");
	if (id > 0) {
		plane.textureIDs.push_back(id);
	}

	id = loadTexture("Assets/Cobble_Stone.jpg");
	if (id > 0) {
		plane.textureIDs.push_back(id);
	}
}

void Application::Update()
{
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(1 * cos(fTime), 0, 0));
	glm::mat4 rotet = glm::rotate(glm::mat4(1), 45.0f, glm::vec3(1, 1.3, 0));
	camPos += camMoveDir;
	matrixes["cam"] = glm::lookAt(camPos, camPos + camFront, glm::vec3(0, 0.6, 0));
	matrixes["proj"] = glm::perspective(glm::radians(50.0f), 3.f / 2.f, 0.1f, 300.0f);

	//matrixes["acc"] = matrixes["proj"] * matrixes["cam"] * rotet;
	matrixes["acc"] = mouseRotateX * mouseRotateY;

	glUniform1f(uniforms["fTime_id"], fTime);
	glUniformMatrix4fv(uniforms["accum_id"], 1, GL_FALSE, glm::value_ptr(matrixes["acc"]));
	glUniformMatrix4fv(uniforms["proyection_id"], 1, GL_FALSE, glm::value_ptr(matrixes["proj"]));
	glUniformMatrix4fv(uniforms["camera_id"], 1, GL_FALSE, glm::value_ptr(matrixes["cam"]));
	glUniformMatrix4fv(uniforms["eye_id"], 1, GL_FALSE, glm::value_ptr(camPos));
}

void Application::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(plane.shader);
	glBindVertexArray(plane.vao);

	glBindTexture(GL_TEXTURE_2D, plane.textureIDs[0]);
	glUniform1i(plane.samplers[0], 0);
	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, plane.textureIDs[1]);
	glUniform1i(plane.samplers[1], 1);
	glActiveTexture(GL_TEXTURE1); //Don't forget to Activate the textures.

	//glDrawArrays(GL_TRIANGLE_STRIP, 0, triangle.numVertex);
	plane.DrawPlane();
	fTime += 0.1f;
}

void Application::Terminate()
{
	//OOOO I AM THE TERMINATOR PEW PEW PEW PEW PUUUSHHHAAAAAAA BOOOOOOOOOOOOOOOM PI PI PI KWHAAAAAAAAAAAAAAAAAAA "AAAAAAH!" 
	//Skynet Skynet.
}
