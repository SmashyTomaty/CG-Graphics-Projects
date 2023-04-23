 #version 430 core

 out vec4 fragColor;
 in vec4 Gouraud;
 in vec2 texCoords;
 uniform float fTime;

 uniform sampler2D samp;

 void main() 
 { 
	//vec4 color = texture(samp, texCoords);
	//fragColor = texture(samp, texCoords);
	fragColor = Gouraud;
 } 