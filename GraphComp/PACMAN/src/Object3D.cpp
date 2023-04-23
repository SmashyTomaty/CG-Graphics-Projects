#include "Object3D.h"

Object3D::~Object3D() {

	if (vbo > 0) {
		glDeleteBuffers(1, &vbo);
	}

	if (vao > 0) {
		glDeleteVertexArrays(1, &vao);
	}

	if (shader > 0) {
		glDeleteProgram(shader);
	}
}

void Object3D::Object3DSetup(GLuint AttrbsToEnable)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, geoBytes + TexBytes, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, geoBytes, (void*)&geoVerts[0]);
	glBufferSubData(GL_ARRAY_BUFFER, geoBytes, TexBytes, (void*)&TextureUV[0]);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(geoBytes));

	//enable attribute arrays per input.
	for (int e = 0; e < AttrbsToEnable; ++e) {
		glEnableVertexAttribArray(e);
	}

	uniforms["fTime_id"] = glGetUniformLocation(shader, "fTime");
	uniforms["mModel_id"] = glGetUniformLocation(shader, "mModel");
	uniforms["proyection_id"] = glGetUniformLocation(shader, "proyection");
	uniforms["camera_id"] = glGetUniformLocation(shader, "camera");
	uniforms["eye_id"] = glGetUniformLocation(shader, "eye");

	GLuint samplerID = glGetUniformLocation(shader, "samp");
	if (samplerID > 0) {
		samplers.push_back(samplerID);
	}

	samplerID = glGetUniformLocation(shader, "texHeight");
	if (samplerID > 0) {
		samplers.push_back(samplerID);
	}
}

void Object3D::Object3DSetMatrix(float fTime, glm::vec3 camPos, glm::vec3 camFront, glm::vec3 hintUp)
{
	matrixes["mod"] = glm::mat4(1);
	matrixes["proj"] = glm::perspective(glm::radians(50.0f), 3.f / 2.f, 0.1f, 300.0f);
	matrixes["cam"] = glm::lookAt(camPos, camPos + camFront, hintUp);

	glUniform1f(uniforms["fTime_id"], fTime);
	glUniformMatrix4fv(uniforms["mModel_id"], 1, GL_FALSE, glm::value_ptr(matrixes["mod"]));
	glUniformMatrix4fv(uniforms["proyection_id"], 1, GL_FALSE, glm::value_ptr(matrixes["proj"]));
	glUniformMatrix4fv(uniforms["camera_id"], 1, GL_FALSE, glm::value_ptr(matrixes["cam"]));
	glUniformMatrix4fv(uniforms["eye_id"], 1, GL_FALSE, glm::value_ptr(camPos));
}

void Object3D::Object3DSetMatrix(float fTime, glm::vec3 camPos, glm::vec3 camFront, glm::vec3 hintUp, glm::mat4 transformation, glm::mat4 rotate, glm::mat4 scale)
{
	Object3DSetMatrix(fTime, camPos, camFront, hintUp);
	matrixes["mod"] = transformation * rotate * scale;

	glUniformMatrix4fv(uniforms["mModel_id"], 1, GL_FALSE, glm::value_ptr(matrixes["mod"]));
}

void Object3D::Object3DSetDraw(float textureCount)
{
	glBindVertexArray(vao);

	for (int e = 0; e < textureCount; ++e) {
		glBindTexture(GL_TEXTURE_2D, textureIDs[e]);
		glUniform1i(samplers[e], e);

		glActiveTexture(GL_TEXTURE0 + e);
	}
}
