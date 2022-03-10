#include <assert.h>
#include <fstream>
#include "Utility.h"
#include "Material.h"
#include "Shader.h"

std::string Material::s_rootFolder = "Assets/Materials/";
std::map<std::string, std::vector<Material>> Material::s_materialGroups;

//This function will load a .mat file with a set of 
//pre-defined materials in there for default settings
//bool Material::LoadMaterials(const std::string& filename)
//{
//
//	if (filename.empty())
//	{
//		return false;
//	}
//
//	std::fstream file(s_rootFolderMaterial + filename, std::ios_base::in);
//
//	//If your application breaks here it means that the material file could 
//	//not be loaded. Possible causes can be a corrupt or missing file. It
//	//could also be that the filename and/or path are incorrectly spelt.
//	assert(file);
//
//	if (!file)
//	{
//		Utility::Log(Utility::Destination::WindowsMessageBox, 
//			"Material file \"" + (s_rootFolderMaterial + filename) + "\"\n\n",
//			Utility::Severity::Failure);
//		return false;
//	}
//
//	std::string line;
//	Material material;
//
//
//
//	std::vector<std::string> subStrings_1;
//	std::vector<std::string> subStrings_2;
//
//	while (!file.eof())
//	{
//		std::getline(file, line);
//		{
//				Utility::RemoveCharacter(line, '[');
//
//			if (!line.empty())
//			{
//			//This means we have reached a block of material data
//			if (line[0] == '[')
//				Utility::RemoveCharacter(line, ']');
//				material.SetName(line);
//			}
//
//			else
//			{
//				Utility::ParseString(line, subStrings_1, '=');
//
//				if (subStrings_1[0] == "ambient")
//				{
//					Utility::ParseString(subStrings_1[1], subStrings_2, ',');
//					material.SetAmbient(std::stof(subStrings_2[0]),
//						std::stof(subStrings_2[1]),
//						std::stof(subStrings_2[2]));
//				}
//
//				if (subStrings_1[0] == "diffuse")
//				{
//					Utility::ParseString(subStrings_1[1], subStrings_2, ',');
//					material.SetDiffuse(std::stof(subStrings_2[0]),
//						std::stof(subStrings_2[1]),
//						std::stof(subStrings_2[2]));
//				}
//
//				if (subStrings_1[0] == "specular")
//				{
//					Utility::ParseString(subStrings_1[1], subStrings_2, ',');
//					material.SetSpecular(std::stof(subStrings_2[0]),
//						std::stof(subStrings_2[1]),
//						std::stof(subStrings_2[2]));
//				}
//
//				if (subStrings_1[0] == "shininess")
//				{
//					material.SetShininess(std::stof(subStrings_1[1]) * 128.0f);
//					s_materials[material.GetName()] = material;
//				}
//
//			}
//
//			subStrings_1.clear();
//			subStrings_2.clear();
//		}
//	}
//
//	file.close();
//	return true;
//}

//This function will load a .mtl file and store 
//all materials into the passed material container
bool Material::LoadMaterials(const std::string& tag, const std::string& filename)
{
	assert(s_materialGroups.find(tag) == s_materialGroups.end());
	std::fstream file(s_rootFolder + filename, std::ios_base::in);

	//If your application breaks here it means that the material file could 
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
				material.m_group.back().SetAmbientMap(subStrings[1]);
				continue;
			}

			//Diffuse texture file
			if (subStrings[0] == "map_Kd")
			{
				material.m_group.back().SetDiffuseMap(subStrings[1]);
				continue;
			}

			//Specular texture file
			if (subStrings[0] == "map_Ks")
			{
				material.m_group.back().SetSpecularMap(subStrings[1]);
				continue;
			}

			//Normal texture file
			if (subStrings[0] == "map_Ns" || subStrings[0] == "bump")
			{
				material.m_group.back().SetNormalMap(subStrings[1]);
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
		// set the group tag for material
	}

	if (!tag.empty())
	{ 
		// set the group tag for material
	}

}

const std::string& Material::GetName() const
{
	return m_name;
}

const std::string& Material::GetNormalMap() const
{
	return m_normalMap;
}

const std::string& Material::GetAmbientMap() const
{
	return m_ambientMap;
}

const std::string& Material::GetDiffuseMap() const
{
	return m_diffuseMap;
}

const std::string& Material::GetSpecularMap() const
{
	return m_specularMap;
}

void Material::SetName(const std::string& name)
{
	m_name = name;
}

//void Material::SetMaterial(const std::string& name)
//{
//
//}

bool Material::IsTextured() const
{
	return m_isTextured;
}

void Material::SetNormalMap(const std::string& normalMap)
{
	m_normalMap = normalMap;
}

void Material::SetAmbientMap(const std::string& ambientMap)
{
	m_ambientMap = ambientMap;
}

void Material::SetDiffuseMap(const std::string& diffuseMap)
{
	m_diffuseMap = diffuseMap;
}

void Material::SetSpecularMap(const std::string& specularMap)
{
	m_specularMap = specularMap;
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