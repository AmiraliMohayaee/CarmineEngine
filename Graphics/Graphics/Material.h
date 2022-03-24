#pragma once

#include <map>
#include "glad.h"
#include <string>
#include <vector>
#include <glm.hpp>
#include "Shader.h"
#include "Texture.h"


class Material
{

public:

	static bool LoadMaterials(const std::string& tag, const std::string& filename);
	static bool Unloading(const std::string& tag);
	static void SetRootFolder(const std::string& rootFolder);

	Material(const std::string& tag = "", const std::string& filename = "");
	~Material() {}

	const std::string& GetTag() const;
	const std::string& GetName() const;

	const Texture& GetNormalMap() const;
	const Texture& GetAmbientMap() const;
	const Texture& GetDiffuseMap() const;
	const Texture& GetSpecularMap() const;

	void SetName(const std::string& name);
	void SetGroup(const std::string& tag);

	bool IsTextured() const;

	void LoadNormalMap(const std::string& tag, const std::string& filename);
	void LoadAmbientMap(const std::string& tag, const std::string& filename);
	void LoadDiffuseMap(const std::string& tag, const std::string& filename);
	void LoadSpecularMap(const std::string& tag, const std::string& filename);


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

	void SetMaterial(const std::string& name);

	void SendToShader(const Shader& shader);

private:

	bool m_isTextured;

	std::string m_tag;
	std::string m_name;
	std::vector<Material> m_group;

	GLfloat m_shininess{ 1.0f };
	GLfloat m_refractiveIndex{ 0.0f };

	Texture m_normalMap;
	Texture m_ambientMap;
	Texture m_diffuseMap;
	Texture m_specularMap;

	glm::vec3 m_ambient{ 0.0f };
	glm::vec3 m_diffuse{ 0.0f };
	glm::vec3 m_specular{ 0.0f };
	glm::vec3 m_emission{ 0.0f };
	glm::vec3 m_transmittance{ 1.0f };

	static std::string s_rootFolder;
	static std::map<std::string, std::vector<Material>> s_materialGroups;
};