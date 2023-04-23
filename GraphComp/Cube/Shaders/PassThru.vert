#version 430 core
	 layout (location = 0) in vec4 vPosition; 
	 layout (location = 1) in vec4 vColor; 
	 uniform float fTime;  //Uniform speaks between the GL tools and the porgramming lenguage.
	 uniform mat4 accum;

	 out vec4 color; 

	 void main() 
	 { 
		 vec4 newPos = accum * vPosition; 
		// rotPos.x = sin(vPosition.x + fTime); 
		// rotPos.y = cos(vPosition.y + fTime); 
		 color = vColor;
		 gl_Position = newPos; 
	 } 
