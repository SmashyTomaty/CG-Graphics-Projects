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

#include "ShaderFuncs.h"
#include "Application.h"

GLfloat vertexPositions[] = {
	1, 1, 0, 1.0f,
	0.66, 1, 0, 1.0f,
	1, 0.66, 0, 1.0f,
	0.66, 0.66, 0, 1.0f
};

GLfloat vertexColors[] = {
	1, 0, 1, 1.0f,
	0, 1, 0, 1.0f,
	0, 1, 0, 1.0f,
	1, 0, 1, 1.0f
};

Application::Application()
{

}

void Application::key_callback(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_RELEASE) {
		glfwSetWindowShouldClose(window, 1);
	}
}

void Application::mouse_callback(double xpos, double ypos)
{
	//std::cout << xpos << ", " << ypos << std::endl;
}

void Application::Setup()
{
	std::string strVertexShader = loadTextFile("Shaders/PassThru.vert");
	std::string strFragmentShader = loadTextFile("Shaders/PassThru.frag");
	InitializeProgram(triangle.shader, strVertexShader, strFragmentShader);
	triangle.numVertex = 4;
	glGenVertexArrays(1, &triangle.vao);
	glBindVertexArray(triangle.vao);
	glGenBuffers(1, &triangle.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, triangle.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions) + sizeof(vertexColors), NULL, GL_STATIC_DRAW); //Static draw is "don't modify"!! For static geometry.
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexPositions), vertexPositions);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexPositions), sizeof(vertexColors), vertexColors);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //stride is space between vertexes. (second to last variable)      
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)sizeof(vertexPositions));

	glEnableVertexAttribArray(0); //enable the vertex array channel at 0
	glEnableVertexAttribArray(1);

	fTime_id = glGetUniformLocation(triangle.shader, "fTime");
	accum_id = glGetUniformLocation(triangle.shader, "accum");
}

void Application::Update()
{
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 100 * cos(fTime)));
	glm::mat4 rotet = glm::rotate(glm::mat4(1), fTime *10, glm::vec3(1,0,0));
	glm::mat4 cam = glm::lookAt(glm::vec3(0,0,3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 3.f / 2.f, 0.1f, 300.0f);
	accum = Projection * cam;

	fTime += 0.01;
}

void Application::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(triangle.shader);
	glBindVertexArray(triangle.vao);

	glUniform1f(fTime_id, fTime);
	glUniformMatrix4fv(accum_id, 1, GL_FALSE, glm::value_ptr(accum));

	//glDrawArrays(GL_TRIANGLE_STRIP, 0, triangle.numVertex);
	glDrawArrays(GL_TRIANGLES, 0, triangle.shader);
	glDrawArrays(GL_TRIANGLES, 1, triangle.shader);
}

void Application::Terminate()
{
	
}
