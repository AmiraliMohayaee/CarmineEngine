#version 460

struct Light
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	vec3 position;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 vertexOut;
in vec4 colorOut;
in vec3 normalOut;
in vec2 textureOut;

out vec4 pixelColor;

uniform Light light;
uniform Material material;

uniform bool isLit;
uniform bool isTextured;
uniform vec3 cameraPosition;

uniform sampler2D textureImage;

void main(void) 
{

	if(isLit)
	{
		//ambient lighting
		vec3 ambientLight = light.ambient * material.ambient;

		//diffuse lighting
		vec3 lightDirection = normalize(light.position - vertexOut);
		float lightIntensity = max(dot(lightDirection, normalOut), 0.0);  //make sure it never falls below 0!
		vec3 diffuseLight = light.diffuse * material.diffuse * lightIntensity;

//		//specular lighting
		vec3 viewDirection = normalize(cameraPosition - vertexOut);
		vec3 reflection = reflect(-lightDirection, normalOut);
		float specularTerm = pow(max(dot(viewDirection, reflection), 0.0), material.shininess);
		vec3 specularLight = light.specular * material.specular * specularTerm;

		// final lighting value
		vec3 finalLight = ambientLight + diffuseLight + specularLight;

		if(isTextured)
		{
			vec2 UV;
			UV.x = textureOut.x;
			UV.y = 1 - textureOut.y;

			pixelColor = vec4(finalLight, 1.0) * texture(textureImage, UV);
		}

		else
		{
			pixelColor = vec4(finalLight, 1.0);
		}
	}

	else if(isTextured)
	{
		vec2 UV;
		UV.x = textureOut.x;
		UV.y = 1 - textureOut.y;

		pixelColor = colorOut * texture(textureImage, UV);
	}

	else
	{
		pixelColor = colorOut;
	}
}