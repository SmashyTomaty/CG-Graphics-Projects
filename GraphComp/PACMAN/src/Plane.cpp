#include "Plane.h"

void Plane::MakePlane(float size)
{
	float offset = 2.0f / size;

	for (float x = -1; x < 1; x += offset) {
		for (float y = -1; y < 1; y += offset) {
			geoVerts.push_back(glm::vec4(x, y, 0, 1));

			geoVerts.push_back(glm::vec4(x + offset, y + offset, 0, 1));

			geoVerts.push_back(glm::vec4(x + offset, y, 0, 1));


			geoVerts.push_back(glm::vec4(x, y, 0, 1));

			geoVerts.push_back(glm::vec4(x, y + offset, 0, 1));

			geoVerts.push_back(glm::vec4(x + offset, y + offset, 0, 1));

			numVertex += 6;
		}
	}

	offset = 1.0f / size;

	for (float x = 0; x < 1; x += offset) {
		for (float y = 0; y < 1; y += offset) {
			TextureUV.push_back(glm::vec2(x, y));

			TextureUV.push_back(glm::vec2(x + offset, y + offset));

			TextureUV.push_back(glm::vec2(x + offset, y));


			TextureUV.push_back(glm::vec2(x, y));

			TextureUV.push_back(glm::vec2(x, y + offset));

			TextureUV.push_back(glm::vec2(x + offset, y + offset));
		}
	}

	for (int e = 0; e < numVertex; e += 4) {
		Colors.push_back(glm::vec4(0, 1, 0, 1));
		Colors.push_back(glm::vec4(1, 0, 0, 1));
		Colors.push_back(glm::vec4(1, 0, 0, 1));
		Colors.push_back(glm::vec4(0, 1, 0, 1));
	}

	geoBytes = geoVerts.size() * 4 * sizeof(float);
	ColBytes = Colors.size() * 4 * sizeof(float);
	TexBytes = TextureUV.size() * 2 * sizeof(float);
}

void Plane::DrawPlane()
{
	glDrawArrays(GL_TRIANGLES, 0, numVertex);
	//for (int e = 0; e < planeVerts.size(); e += 4) {
	//	glDrawArrays(GL_TRIANGLES, e, 3);
	//	glDrawArrays(GL_TRIANGLES, 1 + e, 3);
	//}
}
