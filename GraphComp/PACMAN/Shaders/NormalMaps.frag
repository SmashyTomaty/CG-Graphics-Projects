 #version 430 core

 out vec4 fragColor;
 in vec4 vPos;
 uniform float fTime;

 uniform sampler2D col;
 uniform sampler2D norm;
 uniform vec4 eye;
 uniform mat4 mModel;

 in vec2 texCoords;

vec4 ADS(in vec3 norm, in vec4 pos) {
	vec4 LightDiffuse = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 LightAmbient = vec4(0.2, 0.2, 0.2, 1.0);
	vec4 LightSpecular = vec4(1.0, 1.0, 1.0, 1.0);
	vec4 LightPos = mModel * vec4(-1.0, 0, 0, 1.0);

	vec4 texelCol = texture(col, texCoords);
	vec4 MatDiffuse = texelCol;
	vec4 MatAmbient = texelCol;
	vec4 MatSpecular = texelCol;
	float Shaine = 0.7;

	mat4 TransposeInverse = transpose(inverse(mModel));
	vec4 tNormal = vec4(norm, 1.0);
	tNormal = TransposeInverse * tNormal;

	vec3 newNorm = normalize(tNormal.xyz);

	vec3 lightv = normalize(pos.xyz - LightPos.xyz);
	vec3 viewv = eye.xyz - normalize(pos.xyz);
	vec3 refl = reflect(-lightv, tNormal.xyz);

	vec4 ambient = LightAmbient * MatAmbient;
	vec4 diffuse = LightDiffuse * MatDiffuse * max(0.0, (dot(lightv, newNorm)));
	vec4 specular = vec4(0,0,0,1);
	if (dot(lightv, viewv) > 0.0){
		float temp = pow(max(dot(viewv, refl), 0.0), Shaine);
		specular = LightSpecular * MatSpecular * temp;
	}

	vec4 result = ambient + diffuse + specular;
	vec4 adsColour = clamp(result, 0.0, 1.0);
	adsColour.a = 1.0;

	return adsColour;
};

 void main() 
 { 
	vec4 norma = texture(norm, texCoords);
	vec4 color = ADS(norma.xyz, vPos);
	//vec4 color = texture(col, texCoords);
	//fragColor = texture(samp, texCoords);
	color.a = 1;
	fragColor = color;
 } 
