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

	void MakePlane(float size);
	void DrawPlane();
};