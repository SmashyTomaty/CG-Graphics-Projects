#version 430 core
	 layout (location = 0) in vec4 vPosition; 
	 layout (location = 1) in vec2 vTextCoords; 

	 uniform float fTime;  //Uniform speaks between the GL tools and the porgramming lenguage.
	 uniform mat4 mModel;
	 uniform mat4 proyection; //perspective
	 uniform mat4 camera;

	 out vec2 texCoords;
	 out vec3 normal;
	 out vec4 vPos;

	 void main() 
	 { 

		texCoords = vTextCoords;
		vPos = vPosition;

		gl_Position = proyection * camera * mModel * vPosition; 

	 } 
