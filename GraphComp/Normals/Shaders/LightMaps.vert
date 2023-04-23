#version 430 core
	 layout (location = 0) in vec4 vPosition; 
	 layout (location = 1) in vec2 vTextCoords; 

	 uniform float fTime;  //Uniform speaks between the GL tools and the porgramming lenguage.
	 uniform mat4 accum;

	 out vec2 texCoords;
	 out vec4 Gouraud;

	 vec4 ADS(in vec3 norm, in vec4 pos)
	 {
		vec4 LightDiffuse = vec4(1, 1, 1, 1);
		vec4 LightAmbient = vec4(0, 1, 0, 1);
		vec4 LightSpecular = vec4(1, 1, 1, 1);
		vec4 LightPos = vec4(1, sin(1 * fTime), 1, 1);

		vec4 MatDiffuse = vec4(0.8, 0, 0, 1);
		vec4 MatAmbient = vec4(0, 0, 0, 1);
		vec4 MatSpecular = vec4(0, 0, 0, 1);
		float Shaine = 80.0f;

		vec3 lightv = normalize(pos.xyz - LightPos.xyz);
		vec3 viewv = normalize(pos.xyz);
		vec3 refl = reflect(-lightv, norm);
		vec3 n = normalize(norm);

		vec4 ambient = LightAmbient * MatAmbient;
		vec4 diffuse = LightDiffuse * MatDiffuse * max(0, (dot(lightv, n)));
		vec4 specular = vec4(0,0,0,1);
		if (dot(lightv, viewv) > 0){
			float temp = pow(max(0, dot(viewv, refl)), Shaine);
			specular = LightSpecular * MatSpecular * temp;
		}

		vec4 result = ambient + diffuse + specular;
		vec4 adsColour = clamp(result, 0.1, 1.0);
		adsColour.a = 1;

		return adsColour;
	 };

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
		float time = fTime + 1;
		vec4 newPos = vPosition;
		newPos.z = 0.9 * cos((newPos.x * newPos.x + newPos.y * newPos.y) - fTime);

		texCoords = vTextCoords;
		vec3 normal = calculateNormal(vPosition);
		Gouraud = ADS(normal, newPos);

		gl_Position = accum * newPos; 
	 } 
