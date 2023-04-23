#pragma once
#include <iostream>
#include "GL/glew.h"
#include <GL/GL.h>
#include <GL/GLU.h>

class Object3D {
public:
	GLuint vao, vbo; //Vertex array and Vertex Buffer

	int numVertex; //number of vertexes in object

	GLuint shader; //reference to shaders, the shader is the "program"
};