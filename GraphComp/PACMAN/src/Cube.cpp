#include "Cube.h"

void Cube::MakeCube()
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

	numVertex = 36;

	geoVerts.insert(geoVerts.end(), cube.begin(), cube.end());

	//textures
	glm::vec2 c0(0.0f, 0.0f), c1(1.0f, 1.0f), c2(1.0f, 0.0f),
		c3(0.0f, 1.0f);

	std::vector<glm::vec2> col{
		c0, c1, c2, c0, c3, c1,
		c0, c1, c2, c0, c3, c1,
		c0, c1, c2, c0, c3, c1,
		c0, c1, c2, c0, c3, c1,
		c0, c1, c2, c0, c3, c1,
		c0, c1, c2, c0, c3, c1,
	};

	TextureUV.insert(TextureUV.end(), col.begin(), col.end());

	geoBytes = geoVerts.size() * 4 * sizeof(float);
	TexBytes = TextureUV.size() * 2 * sizeof(float);
}

void Cube::DrawCube()
{
	glDrawArrays(GL_TRIANGLES, 0, numVertex);
}
