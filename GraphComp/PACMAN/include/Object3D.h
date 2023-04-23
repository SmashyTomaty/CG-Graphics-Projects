#pragma once
#include <iostream>
#include "GL/glew.h"
#include <GL/GL.h>
#include <GL/GLU.h>
#include <vector>
#include <map>
#include <glm/mat4X4.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object3D {
public:
	GLuint vao, vbo; //Vertex array and Vertex Buffer
	std::vector<GLuint> textureIDs;
	std::vector<GLuint> samplers;

	std::vector<glm::vec4> geoVerts;
	std::vector<glm::vec2> TextureUV;
	std::vector<glm::vec4> Colors;
	size_t geoBytes;
	size_t TexBytes;
	size_t ColBytes;

	int numVertex; //number of vertexes in object

	GLuint shader; //reference to shaders, the shader is the "program"

	std::map<std::string, GLuint> uniforms; //we use IDs to alocate space to transfer info from GL to Lenguage.
	std::map<std::string, glm::mat4> matrixes;

	void Object3DSetup(GLuint AttrbsToEnable); //send refference to OBJ, not OBJ itself
	void Object3DSetMatrix(float fTime, glm::vec3 camPos, glm::vec3 camFront, glm::vec3 hintUp);
	void Object3DSetMatrix(float fTime, glm::vec3 camPos, glm::vec3 camFront, glm::vec3 hintUp, glm::mat4 transformation, glm::mat4 rotate, glm::mat4 scale);
	void Object3DSetDraw(float textureCount);
	~Object3D();
};