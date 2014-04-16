#version 140

in vec2 fTexUV;
in vec3 fNormal;
in vec3 fLightDir[2];
in vec4 fShadowCoord;

uniform mat4 uMVP;
uniform mat4 uMV;
uniform mat3 uN;
uniform sampler2D uTex;
uniform sampler2DShadow uShadowMap;
uniform vec3 uLightPos[2];
uniform vec4 uLightColor[2];
uniform vec4 uAmbient;

// Light params; these could become uniforms
const float constantAttenuation = 0.3;
const float linearAttenuation = 0.1;
const float quadraticAttenuation = 0.01;

void main()
{
	vec4 light = uAmbient;
	float NdotL, dist, att;

	for (int i = 0; i < 1; i++) {
		// Dot product affects strength of light
		NdotL = max(0.0, dot(normalize(fNormal), normalize(fLightDir[i])));
	
		// Calculate attenuation
		dist = -length(fLightDir[i]) * uLightColor[i].a;
		att = 1.0 / (constantAttenuation + linearAttenuation*dist + quadraticAttenuation*dist*dist);
	
		// Calculate brightness
		light += uLightColor[i] * NdotL;
		
		// Reflections
		vec3 vReflection = normalize(reflect(-normalize(fLightDir[i]),normalize(fNormal)));
		float spec = max(0.0, dot(normalize(fNormal), vReflection));
		float fSpec = pow(spec, 64.0);
		light += vec4(fSpec, fSpec, fSpec, 0.0f);
	}
	
	// Shadow
	float visibility = texture(uShadowMap, fShadowCoord.xyz) + 0.5;

	gl_FragColor = texture(uTex, fTexUV) * light * visibility;
}