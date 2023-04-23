#include <iostream>

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

std::vector<glm::vec4> Application::CreateCube() 
{
	glm::vec4 v0{ -1.0f, 1.0f, 1.0f, 1.0f }, v1{ 1.0f, 1.0f, 1.0f, 1.0f }, 
			v2{ 1.0f, -1.0f, 1.0f, 1.0f }, v3{ -1.0f, -1.0f, 1.0f, 1.0f }, 
			v4{ 1.0f, 1.0f, -1.0f, 1.0f }, v5{ -1.0f, 1.0f, -1.0f, 1.0f },
			v6{ -1.0f, -1.0f, -1.0f, 1.0f }, v7{ 1.0f, -1.0f, -1.0f, 1.0f };


	std::vector<glm::vec4> cube{
		v0, v2, v1, v0, v3, v2,
		v1, v7, v4, v1, v2, v7,
		v4, v6, v5, v4, v7, v6,
		v5, v3, v0, v5, v6, v3,
		v5, v1, v4, v5, v0, v1,
		v3, v7, v2, v3, v6, v7,
	};

	return cube;
}

std::vector<glm::vec4> Application::ColourCube()
{
	glm::vec4 c0(1, 0, 0, 1.0f), c1(0, 1, 0, 1.0f), c2(0, 0, 1, 1.0f),
		c3(1, 1, 0, 1.0f), c4(1, 0, 0.5f, 1.0f), c5(1, 1, 1, 1.0f);

	std::vector<glm::vec4> col{
		c0, c0, c0, c0, c0, c0,
		c1, c1, c1, c1, c1, c1,
		c2, c2, c2, c2, c2, c2,
		c3, c3, c3, c3, c3, c3,
		c4, c4, c4, c4, c4, c4,
		c5, c5, c5, c5, c5, c5,
	};

	return col;
}

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
	InitializeProgram(cube.shader, strVertexShader, strFragmentShader);
	std::vector<glm::vec4> cubeColour = ColourCube();
	std::vector<glm::vec4> cubeGeometry = CreateCube();
	cube.numVertex = cubeGeometry.size();

	size_t Cubebytes = cubeGeometry.size() * 4 * sizeof(float);
	size_t Colorbytes = cubeColour.size() * 4 * sizeof(float);

	glGenVertexArrays(1, &cube.vao);
	glBindVertexArray(cube.vao);
	glGenBuffers(1, &cube.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, cube.vbo);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions) + sizeof(vertexColors), NULL, GL_STATIC_DRAW); //Static draw is "don't modify"!! For static geometry.
	//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexPositions), vertexPositions);
	//glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertexPositions), sizeof(vertexColors), vertexColors);
	glBufferData(GL_ARRAY_BUFFER, Cubebytes + Colorbytes, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, Cubebytes, (void*)&cubeGeometry[0]);
	glBufferSubData(GL_ARRAY_BUFFER, Cubebytes, Colorbytes, (void*)&cubeColour[0]);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); //stride is space between vertexes. (second to last variable)      
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)Cubebytes);

	glEnableVertexAttribArray(0); //enable the vertex array channel at 0
	glEnableVertexAttribArray(1);

	fTime_id = glGetUniformLocation(cube.shader, "fTime");
	accum_id = glGetUniformLocation(cube.shader, "accum");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //grafica en modo wireframe
}

void Application::Update()
{
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 100 * cos(fTime)));
	glm::mat4 rotet = glm::rotate(glm::mat4(1), fTime*10, glm::vec3(0.4f,0.7f,0.3f));
	glm::mat4 cam = glm::lookAt(glm::vec3(0,0,20), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 3.f / 2.f, 0.1f, 300.0f);
	accum = Projection * cam * rotet;

	fTime += 0.01;
}

void Application::Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(cube.shader);
	glBindVertexArray(cube.vao);

	glUniform1f(fTime_id, fTime);
	glUniformMatrix4fv(accum_id, 1, GL_FALSE, glm::value_ptr(accum));

	//glDrawArrays(GL_TRIANGLE_STRIP, 0, triangle.numVertex);
	glDrawArrays(GL_TRIANGLES, 0, cube.numVertex);
}

void Application::Terminate()
{
	
}
