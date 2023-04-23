 #version 430 core

 out vec4 fragColor;
 in vec3 normal;
 in vec4 vPos;
 uniform float fTime;

 uniform sampler2D samp;
 uniform vec4 eye;
 uniform mat4 accum;

 in vec2 texCoords;

vec4 ADS(in vec3 norm, in vec4 pos) {
	vec4 LightDiffuse = vec4(1, 1, 1, 1);
	vec4 LightAmbient = vec4(0.3, 0.3, 0.3, 1);
	vec4 LightSpecular = vec4(1, 0.5, 1, 1);
	vec4 LightPos = accum * vec4(0, -0.5, -2, 1);

	vec4 MatDiffuse = vec4(1, 0, 0, 1);
	vec4 MatAmbient = vec4(1, 1, 1, 1);
	vec4 MatSpecular = vec4(0, 0, 0, 1);
	float Shaine = 80.0;

	mat4 TransposeInverse = transpose(inverse(accum));
	vec4 tNormal = vec4(norm, 1);
	tNormal = TransposeInverse * tNormal;

	vec3 newNorm = normalize(tNormal.xyz);

	vec3 lightv = normalize(pos.xyz - LightPos.xyz);
	vec3 viewv = eye.xyz - normalize(pos.xyz);
	vec3 refl = reflect(-lightv, tNormal.xyz);

	vec4 ambient = LightAmbient * MatAmbient;
	vec4 diffuse = LightDiffuse * MatDiffuse * max(0, (dot(lightv, newNorm)));
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

 void main() 
 { 
	vec4 color = ADS(normal, vPos);
	//vec4 color = texture(samp, texCoords);
	//fragColor = texture(samp, texCoords);
	color.a = 1;
	fragColor = color;
 } 
