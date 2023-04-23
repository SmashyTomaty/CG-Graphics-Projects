 #version 430 core

 out vec4 fragColor;
 in vec2 texCoords;
 uniform float fTime;

 uniform sampler2D col;
 uniform vec4 eye;
 uniform mat4 mModel;

 void main() 
 { 
    vec2 uv = texCoords;

    uv = 2.0 * uv - 1.0;

    float wave = sin(fTime);

    float circle = uv.x * uv.x + uv.y * uv.y;

    vec4 color1 = vec4(vec3(circle + wave),1.0);
	vec4 color2 = texture(col, texCoords);
    vec4 color = mix(color1, color2, 0.5);
    
	fragColor = color;
 } 

 // Partially taken from https://gamedev.stackexchange.com/questions/83853/how-to-implement-color-changing-fragment-shader
 // Therfore code doesn't belong to me.