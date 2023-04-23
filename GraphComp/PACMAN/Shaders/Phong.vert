#version 430 core
	 layout (location = 0) in vec4 vPosition; 
	 layout (location = 1) in vec2 vTextCoords; 

	 uniform float fTime;  //Uniform speaks between the GL tools and the porgramming lenguage.
	 uniform mat4 accum;
	 uniform mat4 proyection; //perspective
	 uniform mat4 camera;

	 out vec2 texCoords;
	 out vec3 normal;
	 out vec4 vPos;

	 float Dp(float a, float b){
		 return 2 * cos (.005 * (a*a + b*b) - fTime) * 0.005 * 2 * a;
	 }

	 vec3 calculateNormal(vec4 v){
		vec3 v1 = vec3(1, Dp(v.x, v.z), 0);
		vec3 v2 = vec3(0, Dp(v.z, v.x), 1);

		return normalize(cross(v2, v1));
	 }

	 void main() 
	 { 
		vec4 newPos = vPosition;
		//newPos.z = 0.2 * sin(2 * (((newPos.x * newPos.x) + (newPos.y * newPos.y))) - fTime);

		texCoords = vTextCoords;
		normal = calculateNormal(vPosition);
		vPos = newPos;

		gl_Position = proyection * camera * accum * newPos; 
	 } 
