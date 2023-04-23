#version 430 core
	 layout (location = 0) in vec4 vPosition; 
	 layout (location = 1) in vec2 vTextCoords; 
	 uniform float fTime;  //Uniform speaks between the GL tools and the porgramming lenguage.
	 uniform mat4 accum;

	 out vec4 color; 
	 out vec2 texCoords;

	 void main() 
	 { 
		vec4 newPos = accum * vPosition; 
		texCoords = vTextCoords;
		gl_Position = newPos; 
	 } 
