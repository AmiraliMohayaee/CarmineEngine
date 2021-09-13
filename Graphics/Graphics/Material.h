#pragma once

#include <map>
#include <string>
#include <vector>
#include <glm.hpp>
#include "glad.h"
#include "Shader.h"


class Material
{

public:

	static bool LoadMaterials(const std::string& filename);
	static bool LoadMaterials(std::vector<Material>& materials, const std::string& filename);

	Material();

	const std::string& GetName() const;
	const std::string& GetNormalMap() const;
	const std::string& GetAmbientMap() const;
	const std::string& GetDiffuseMap() const;
	const std::string& GetSpecularMap() const;

	void SetName(const std::string& name);
	void SetMaterial(const std::string& name);

	void SetNormalMap(const std::string& normalMap);
	void SetAmbientMap(const std::string& ambientMap);
	void SetDiffuseMap(const std::string& diffuseMap);
	void SetSpecularMap(const std::string& specularMap);

	void SetShininess(GLfloat shininess);
	void SetRefractiveIndex(GLfloat refractiveIndex);

	void SetAmbient(const glm::vec3& ambient);
	void SetAmbient(GLfloat r, GLfloat g, GLfloat b);

	void SetDiffuse(const glm::vec3& diffuse);
	void SetDiffuse(GLfloat r, GLfloat g, GLfloat b);

	void SetSpecular(const glm::vec3& specular);
	void SetSpecular(GLfloat r, GLfloat g, GLfloat b);

	void SetEmission(const glm::vec3& emission);
	void SetEmission(GLfloat r, GLfloat g, GLfloat b);

	void SetTransmittance(const glm::vec3& transmittance);
	void SetTransmittance(GLfloat r, GLfloat g, GLfloat b);

	void SendToShader(const Shader& shader);

private:

	static std::string s_rootFolderMaterial;
	static std::map<std::string, Material> s_materials;

	std::string m_name;
	GLfloat m_shininess;
	GLfloat m_refractiveIndex;

	std::string m_normalMap;
	std::string m_ambientMap;
	std::string m_diffuseMap;
	std::string m_specularMap;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;
	glm::vec3 m_emission;
	glm::vec3 m_transmittance;

};