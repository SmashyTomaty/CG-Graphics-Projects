#include "Plane.h"

void Plane::MakePlane(float size)
{
	float offset = 2.0f / size;

	for (float x = -1; x < 1; x += offset) {
		for (float y = -1; y < 1; y += offset) {
			planeVerts.push_back(glm::vec4(x, y, 0, 1));

			planeVerts.push_back(glm::vec4(x + offset, y + offset, 0, 1));

			planeVerts.push_back(glm::vec4(x + offset, y, 0, 1));


			planeVerts.push_back(glm::vec4(x, y, 0, 1));

			planeVerts.push_back(glm::vec4(x, y + offset, 0, 1));

			planeVerts.push_back(glm::vec4(x + offset, y + offset, 0, 1));

			numVertex += 6;
		}
	}

	offset = 1.0f / size;

	for (float x = offset; x < 1; x += offset) {
		for (float y = offset; y < 1; y += offset) {
			planeTextures.push_back(glm::vec2(x + offset, y));

			planeTextures.push_back(glm::vec2(x, y));

			planeTextures.push_back(glm::vec2(x + offset, y + offset));

			planeTextures.push_back(glm::vec2(x, y + offset));
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
	glDrawArrays(GL_TRIANGLES, 0, numVertex);
	//for (int e = 0; e < planeVerts.size(); e += 4) {
	//	glDrawArrays(GL_TRIANGLES, e, 3);
	//	glDrawArrays(GL_TRIANGLES, 1 + e, 3);
	//}
}
