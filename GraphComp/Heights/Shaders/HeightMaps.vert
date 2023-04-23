#version 430 core
	 layout (location = 0) in vec4 vPosition; 
	 layout (location = 1) in vec2 vTextCoords; 

	 uniform float fTime;  //Uniform speaks between the GL tools and the porgramming lenguage.
	 uniform mat4 accum;

	 uniform sampler2D texHeight;

	 out vec4 color; 
	 out vec2 texCoords;

	 void main() 
	 { 
		vec4 color = texture(texHeight, vTextCoords);
		float luminosity = ((0.2126*color.r) + (0.7152*color.g) + (0.0722*color.b));
		vec4 newPos = vPosition;
		newPos.y =  14 * luminosity;

		texCoords = vTextCoords;

		gl_Position = accum * newPos; 
	 } 
