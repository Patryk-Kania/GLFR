#ifndef GLFR_DEFAULT_SHADERS_HH
#define GLFR_DEFAULT_SHADERS_HH

namespace glfr
{
	const char *pDefaultVertexShaderSource = R"VS(
#version 330 core

layout ( location = 0 ) in vec3 vertexPos;
layout ( location = 1 ) in vec2 vertexUV;
layout ( location = 2 ) in vec3 vertexNormal;

uniform mat4 mvpMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

out vec3 fragPos;
out vec2 fragUV;
out vec3 fragNormal;

void main()
{
	fragPos = vec3( modelMatrix * vec4(vertexPos, 1.0 ) );
	fragUV = vertexUV;
	fragNormal = normalMatrix * vertexNormal;
	gl_Position = mvpMatrix * vec4( vertexPos, 1.0 );
}
	)VS";

	const char *pDefaultFragmentShaderSource = R"FS(
#version 330 core

struct Material
{
	bool isAffectedByLight;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	vec3 emissiveColor;
	float opacity;
	float specularPower;
	float alphaThreshold;

	bool hasAmbientTexture;
	bool hasDiffuseTexture;
	bool hasSpecularTexture;
	bool hasEmissiveTexture;
	bool hasSpecularPowerTexture;
	bool hasOpacityTexture;
	bool hasNormalTexture;

	sampler2D ambientTexture;
	sampler2D diffuseTexture;
	sampler2D specularTexture;
	sampler2D emissiveTexture;
	sampler2D specularPowerTexture;
	sampler2D opacityTexture;
	sampler2D normalTexture;
};

const int kMaxNumOfLights = 10;
const int kPointLightType = 0;
const int kSpotLightType = 1;
const int kDirectionalLightType = 2;

struct Light
{
	vec3 position;
	vec3 direction;
	vec3 color;
	float spotAngle;
	float range;
	float intensity;
	bool enabled;
	int type;
};

in vec3 fragPos;
in vec2 fragUV;
in vec3 fragNormal;

uniform vec3 cameraPos;
uniform vec3 globalAmbient;
uniform Material material;
uniform int numOfLights;
uniform Light lights[kMaxNumOfLights];

out vec4 fragColor;

vec3 calculateDiffuseLight( vec3 color, vec3 lightVec, vec3 normal )
{
	float NdotL = max( dot( normal, lightVec ), 0.0 );
	return color * NdotL;
}

vec3 calculateSpecularLight( vec3 color, vec3 lightVec, vec3 viewVec, vec3 normal, float power )
{
	vec3 reflectionVec = normalize( reflect( -lightVec, normal ) );
	float RdotV = max( dot( reflectionVec, viewVec ), 0.0 );
	return color * pow( RdotV, power );
}

float calculateLightAttenuation( float lightRange, float distToLight )
{
	float smoothness = 0.75;
	return 1.0f - smoothstep( lightRange * smoothness, lightRange, distToLight );
}

void calculatePointLight( Light light, vec3 viewVec, vec3 normal, float shininess, inout vec3 diffuse, inout vec3 specular )
{
	vec3 lightVec = light.position - fragPos;
	float distance = length( lightVec );
	lightVec = lightVec / distance;

	float attenuation = calculateLightAttenuation( light.range, distance );

	diffuse = diffuse + calculateDiffuseLight( light.color, lightVec, normal ) * attenuation * light.intensity;
	specular = specular + calculateSpecularLight( light.color, lightVec, viewVec, normal, shininess ) * attenuation * light.intensity;
}

float calculateSpotCone( Light light, vec3 lightVec )
{
	float minCos = cos( radians( light.spotAngle ) );
	float maxCos = mix( minCos, 1, 0.5f );
	float cosAngle = dot( light.direction, -lightVec );

	return smoothstep( minCos, maxCos, cosAngle );
}

void calculateSpotLight( Light light, vec3 viewVec, vec3 normal, float shininess, inout vec3 diffuse, inout vec3 specular )
{
	vec3 lightVec = light.position - fragPos;
	float distance = length( lightVec );
	lightVec = lightVec / distance;

	float attenuation = calculateLightAttenuation( light.range, distance );
	float spotIntensity = calculateSpotCone( light, lightVec );

	diffuse = diffuse + calculateDiffuseLight( light.color, lightVec, normal ) * attenuation * spotIntensity * light.intensity;
	specular = specular + calculateSpecularLight( light.color, lightVec, viewVec, normal, shininess) * attenuation * spotIntensity * light.intensity;
}

void calculateDirectionalLight( Light light, vec3 viewVec, vec3 normal, float shininess, inout vec3 diffuse, inout vec3 specular )
{

	vec3 lightVec = normalize( -light.direction );

	diffuse = diffuse + calculateDiffuseLight( light.color, lightVec, normal ) * light.intensity;
	specular = specular + calculateSpecularLight( light.color, lightVec, viewVec, normal, shininess ) * light.intensity;
}

void main()
{
	if( !material.isAffectedByLight )
	{
		fragColor = vec4( material.diffuseColor, 1.0 );
	}
	else
	{
		vec3 ambient = material.ambientColor;
		if( material.hasAmbientTexture )
		{
			ambient = vec3( texture( material.ambientTexture, fragUV ) );
		}
		ambient = ambient * globalAmbient;

		vec3 diffuse = material.diffuseColor;
		if( material.hasDiffuseTexture )
		{
			diffuse = vec3( texture( material.diffuseTexture, fragUV ) );
		}

		vec3 specular = material.specularColor;
		if( material.hasSpecularTexture )
		{
			specular = vec3( texture( material.specularTexture, fragUV ) );
		}

		vec3 emissive = material.emissiveColor;
		if( material.hasEmissiveTexture )
		{
			emissive = vec3( texture( material.emissiveTexture, fragUV ) );
		}

		float shininess = material.specularPower;
		if( material.hasSpecularPowerTexture )
		{
			shininess = float( texture( material.specularPowerTexture, fragUV ) );
		}

		float alpha = material.opacity;
		if( material.hasOpacityTexture )
		{
			alpha = float( texture( material.opacityTexture, fragUV ) );
		}

		vec3 normal = normalize( fragNormal );
		if( material.hasNormalTexture )
		{
			normal = normalize( vec3( texture( material.normalTexture, fragUV ) ) );
		}

		vec3 lightsDiffuse = vec3( 0.0 );
		vec3 lightsSpecular = vec3( 0.0 );
		vec3 viewVec = normalize( cameraPos - fragPos );
		for( int i = 0; i < numOfLights; i++ )
		{
			if( !lights[i].enabled )
				continue;

			if( lights[i].type != kDirectionalLightType &&
			    distance( lights[i].position, fragPos ) > lights[i].range )
				continue;

			switch(lights[i].type)
			{
				case kDirectionalLightType:
					calculateDirectionalLight( lights[i], viewVec, normal, shininess, lightsDiffuse, lightsSpecular );
					break;

				case kPointLightType:
					calculatePointLight( lights[i], viewVec, normal, shininess, lightsDiffuse, lightsSpecular );
					break;

				case kSpotLightType:
					calculateSpotLight( lights[i], viewVec, normal, shininess, lightsDiffuse, lightsSpecular );
					break;
			}
		}

		diffuse = diffuse * lightsDiffuse;
		if( shininess < 1.0 )
		{
			specular = vec3( 0.0 );
		}
		else
		{
			specular = specular * lightsSpecular;
		}

		vec3 result = ambient + emissive + diffuse + specular;
		fragColor = vec4( result, alpha );
	}
}
	)FS";
}

#endif
