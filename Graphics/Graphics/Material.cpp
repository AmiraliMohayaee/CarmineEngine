#include <assert.h>
#include <fstream>
#include "Utility.h"
#include "Material.h"
#include "Shader.h"

std::string Material::s_rootFolder = "Assets/Materials/";
std::map<std::string, std::vector<Material>> Material::s_materialGroups;

//This function will load a .mtl file and store 
//all materials into the passed material container
bool Material::LoadMaterials(const std::string& tag, const std::string& filename)
{

	assert(s_materialGroups.find(tag) == s_materialGroups.end());
	std::fstream file(s_rootFolder + filename, std::ios_base::in);

	//If your application breaks here it means that the material file could 
	//not be loaded. Possible causes can be a corrupt or missing file. It
	//not be loaded. Possible causes can be a corrupt or missing file. It
	//could also be that the filename and/or path are incorrectly spelt.
	assert(file);

	if (!file)
	{
		Utility::Log(Utility::Destination::WindowsMessageBox,
			"Error loading material file \"" + (s_rootFolder + filename) + "\"\n\n",
			Utility::Severity::Failure);
		return false;
	}

	Material material;
	//material.m_tag = tag;
	//material.m_group.reserve(5);

	std::string line;
	std::vector<std::string> subStrings;

	while (!file.eof())
	{
		getline(file, line);

		if (!line.empty())
		{

			subStrings.clear();
			Utility::ParseString(line, subStrings, ' ');

			//Add the material into the container. All properties from now will add to this
			//material which is the start of a material grouping matching the OBJ grouping
			if (subStrings[0] == "newmtl")
			{
				material.m_group.push_back(Material());
				material.m_group.back().SetName(subStrings[1]);
				continue;
			}

			//Ambient RGB values
			if (subStrings[0] == "Ka")
			{
				material.m_group.back().SetAmbient(std::stof(subStrings[1]),
					std::stof(subStrings[2]),
					std::stof(subStrings[3]));
				continue;
			}

			//Diffuse RGB values
			if (subStrings[0] == "Kd")
			{
				material.m_group.back().SetDiffuse(std::stof(subStrings[1]),
					std::stof(subStrings[2]),
					std::stof(subStrings[3]));
				continue;
			}

			//Specular RGB values
			if (subStrings[0] == "Ks")
			{
				material.m_group.back().SetSpecular(std::stof(subStrings[1]),
					std::stof(subStrings[2]),
					std::stof(subStrings[3]));
				continue;
			}

			//Transmittance RGB values which is the ratio of the light 
			//energy falling on a surface to that transmitted through it
			if (subStrings[0] == "Kt")
			{
				material.m_group.back().SetTransmittance(std::stof(subStrings[1]),
					std::stof(subStrings[2]),
					std::stof(subStrings[3]));
				continue;
			}

			//Emission RGB values
			if (subStrings[0] == "Ke")
			{
				material.m_group.back().SetEmission(std::stof(subStrings[1]),
					std::stof(subStrings[2]),
					std::stof(subStrings[3]));
				continue;
			}

			//Refractive index scalar value which is the measure of the 
			//bending of light when passing from one medium into another
			if (subStrings[0] == "Ni")
			{
				material.m_group.back().SetRefractiveIndex(std::stof(subStrings[1]));
				continue;
			}

			//Specular exponent or shininess value (possible 0 - 1000)
			if (subStrings[0] == "Ns")
			{
				material.m_group.back().SetShininess(std::stof(subStrings[1]));
				continue;
			}

			//Ambient texture file
			if (subStrings[0] == "map_Ka")
			{
				material.m_group.back().LoadAmbientMap(subStrings[1], subStrings[1]);
				continue;
			}

			//Diffuse texture file
			if (subStrings[0] == "map_Kd")
			{
				material.m_group.back().LoadDiffuseMap(subStrings[1], subStrings[1]);
				continue;
			}

			//Specular texture file
			if (subStrings[0] == "map_Ks")
			{
				material.m_group.back().LoadSpecularMap(subStrings[1], subStrings[1]);
				continue;
			}

			//Normal texture file
			if (subStrings[0] == "map_Ns" || subStrings[0] == "bump")
			{
				material.m_group.back().LoadNormalMap(subStrings[1], subStrings[1]);
				continue;
			}

		}

	}

	file.close();
	s_materialGroups[tag] = material.m_group;

	return true;
}

bool Material::Unloading(const std::string& tag)
{
	return false;
}

void Material::SetRootFolder(const std::string& rootFolder)
{
	s_rootFolder = rootFolder;
}

Material::Material(const std::string& tag, const std::string& filename)
{
	m_isTextured = false;
	m_shininess = 1.0f;
	m_refractiveIndex = 0.0f;
	m_ambient = glm::vec3(0.0f);
	m_diffuse = glm::vec3(0.0f);
	m_specular = glm::vec3(0.0f);
	m_emission = glm::vec3(0.0f);
	m_transmittance = glm::vec3(1.0f);

	if (!filename.empty())
	{
		LoadMaterials(tag, filename);
		SetGroup(tag);
	}

	else if (!tag.empty())
	{ 
		SetGroup(tag);
	}

}

const std::string& Material::GetTag() const
{
	// TODO: insert return statement here
}

const std::string& Material::GetName() const
{
	return m_name;
}

const Texture& Material::GetNormalMap() const
{
	return m_normalMap;
}

const Texture& Material::GetAmbientMap() const
{
	return m_ambientMap;
}

const Texture& Material::GetDiffuseMap() const
{
	return m_diffuseMap;
}

const Texture& Material::GetSpecularMap() const
{
	return m_specularMap;
}

void Material::SetName(const std::string& name)
{
	m_name = name;
}

void Material::SetGroup(const std::string& tag)
{
	auto it = s_materialGroups.find(tag);
	assert(it != s_materialGroups.end());
	m_group = it->second;
}

void Material::SetMaterial(const std::string& name)
{

}

bool Material::IsTextured() const
{
	return m_isTextured;
}

void Material::LoadNormalMap(const std::string& tag, const std::string& filename)
{
	m_normalMap.Load(tag, filename);
	m_normalMap.SetTexture(tag);
	m_isTextured = true;
}

void Material::LoadAmbientMap(const std::string& tag, const std::string& filename)
{
	m_ambientMap.Load(tag, filename);
	m_ambientMap.SetTexture(tag);
	m_isTextured = true;
}

void Material::LoadDiffuseMap(const std::string& tag, const std::string& filename)
{
	m_diffuseMap.Load(tag, filename);
	m_diffuseMap.SetTexture(tag);
	m_isTextured = true;
}

void Material::LoadSpecularMap(const std::string& tag, const std::string& filename)
{
	m_specularMap.Load(tag, filename);
	m_specularMap.SetTexture(tag);
	m_isTextured = true;
}

void Material::SetShininess(GLfloat shininess)
{
	m_shininess = shininess;
}

void Material::SetRefractiveIndex(GLfloat refractiveIndex)
{
	m_refractiveIndex = refractiveIndex;
}

void Material::SetAmbient(const glm::vec3& ambient)
{
	m_ambient = ambient;
}

void Material::SetAmbient(GLfloat r, GLfloat g, GLfloat b)
{
	m_ambient.r = r;
	m_ambient.g = g;
	m_ambient.b = b;
}

void Material::SetDiffuse(const glm::vec3& diffuse)
{
	m_diffuse = diffuse;
}

void Material::SetDiffuse(GLfloat r, GLfloat g, GLfloat b)
{
	m_diffuse.r = r;
	m_diffuse.g = g;
	m_diffuse.b = b;
}

void Material::SetSpecular(const glm::vec3& specular)
{
	m_specular = specular;
}

void Material::SetSpecular(GLfloat r, GLfloat g, GLfloat b)
{
	m_specular.r = r;
	m_specular.g = g;
	m_specular.b = b;
}

void Material::SetEmission(const glm::vec3& emission)
{
	m_emission = emission;
}

void Material::SetEmission(GLfloat r, GLfloat g, GLfloat b)
{
	m_emission.r = r;
	m_emission.g = g;
	m_emission.b = b;
}

void Material::SetTransmittance(const glm::vec3& transmittance)
{
	m_transmittance = transmittance;
}

void Material::SetTransmittance(GLfloat r, GLfloat g, GLfloat b)
{
	m_transmittance.r = r;
	m_transmittance.g = g;
	m_transmittance.b = b;
}

void Material::SendToShader(const Shader& shader)
{
	shader.SendData("material.ambient", m_ambient);
	shader.SendData("material.diffuse", m_diffuse);
	shader.SendData("material.specular", m_specular);
	shader.SendData("material.shininess", m_shininess);
}