#pragma once
#include <iostream>
#include "GL/glew.h"
#include <GL/GL.h>
#include <GL/GLU.h>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include "Object3D.h"

class Plane : public Object3D  {
public:

	std::vector<glm::vec4> planeVerts;
	std::vector<glm::vec2> planeTextures;
	std::vector<glm::vec4> planeColor;
	size_t planeBytes;
	size_t planeCols;
	size_t planeTex;

	void MakePlane(float size);
	void DrawPlane();
};