 #version 430 core

 out vec4 fragColor;
 in vec2 texCoords;
 uniform float fTime;

 uniform sampler2D samp;
 uniform sampler2D samp2;

 void main() 
 { 
	vec4 color = texture(samp, texCoords);
	vec4 color1 = texture(samp2, texCoords);
	fragColor = mix(color, color1, fTime);
 } 