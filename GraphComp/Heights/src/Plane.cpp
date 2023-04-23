#include "Plane.h"

void Plane::MakePlane(float size)
{
	float offset = 2.0f / size;

	for (float x = -1; x < 1; x += offset) {
		for (float y = -1; y < 1; y += offset) {
			planeVerts.push_back(glm::vec4(x, y, 0, 1));
			planeTextures.push_back(glm::vec2(x * 2, y * 2));

			planeVerts.push_back(glm::vec4(x + offset, y, 0, 1));
			planeTextures.push_back(glm::vec2((x + offset) * 2, y * 2));

			planeVerts.push_back(glm::vec4(x, y + offset, 0, 1));
			planeTextures.push_back(glm::vec2(x * 2, (y + offset) * 2));

			planeVerts.push_back(glm::vec4(x + offset, y + offset, 0, 1));
			planeTextures.push_back(glm::vec2((x + offset) * 2, (y + offset) * 2));

			numVertex += 4;
		}
	}

	for (int e = 0; e < numVertex; e += 4) {
		planeColor.push_back(glm::vec4(0, 1, 0, 1));
		planeColor.push_back(glm::vec4(1, 0, 0, 1));
		planeColor.push_back(glm::vec4(1, 0, 0, 1));
		planeColor.push_back(glm::vec4(0, 1, 0, 1));
	}

	planeBytes = planeVerts.size() * 4 * sizeof(float);
	planeCols = planeColor.size() * 4 * sizeof(float);
	planeTex = planeTextures.size() * 4 * sizeof(float);
}

void Plane::DrawPlane()
{
	for (int e = 0; e < planeVerts.size(); e += 4) {
		glDrawArrays(GL_TRIANGLES, e, 3);
		glDrawArrays(GL_TRIANGLES, e + 1, 3);
	}
}
